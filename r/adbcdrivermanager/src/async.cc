
// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

#include <deque>
#include <future>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include <adbc.h>

#include "radbc.h"

enum class RAdbcAsyncTaskStatus { NOT_STARTED, STARTED, READY };

struct RAdbcAsyncTask {
  AdbcError* return_error{nullptr};
  int* return_code{nullptr};

  RAdbcAsyncTaskStatus status;
  std::future<void> result;
};

template <>
inline const char* adbc_xptr_class<RAdbcAsyncTask>() {
  return "adbc_async_task";
}

static void FinalizeTaskXptr(SEXP task_xptr) {
  auto task = reinterpret_cast<RAdbcAsyncTask*>(R_ExternalPtrAddr(task_xptr));
  if (task != nullptr) {
    delete task;
  }
}

static void error_for_started_task(RAdbcAsyncTask* task) {
  if (task->result.valid()) {
    Rf_error("adbc_async_task is already in use");
  }
}

extern "C" SEXP RAdbcAsyncTaskNew(SEXP error_xptr) {
  const char* names[] = {"error_xptr", "return_code", "user_data", ""};
  SEXP task_prot = PROTECT(Rf_mkNamed(VECSXP, names));

  SET_VECTOR_ELT(task_prot, 0, error_xptr);

  SEXP return_code_sexp = PROTECT(Rf_allocVector(INTSXP, 1));
  SET_VECTOR_ELT(task_prot, 1, return_code_sexp);
  UNPROTECT(1);

  SEXP new_env = PROTECT(adbc_new_env());
  SET_VECTOR_ELT(task_prot, 2, new_env);
  UNPROTECT(1);

  auto task = new RAdbcAsyncTask();
  SEXP task_xptr = PROTECT(R_MakeExternalPtr(task, R_NilValue, task_prot));
  R_RegisterCFinalizer(task_xptr, &FinalizeTaskXptr);

  task->return_error = adbc_from_xptr<AdbcError>(error_xptr);
  task->return_code = INTEGER(VECTOR_ELT(task_prot, 1));

  *(task->return_code) = NA_INTEGER;
  task->status = RAdbcAsyncTaskStatus::NOT_STARTED;

  UNPROTECT(2);
  return task_xptr;
}

extern "C" SEXP RAdbcAsyncTaskData(SEXP task_xptr) {
  adbc_from_xptr<RAdbcAsyncTask>(task_xptr);
  return R_ExternalPtrProtected(task_xptr);
}

extern "C" SEXP RAdbcAsyncTaskWaitFor(SEXP task_xptr, SEXP duration_ms_sexp) {
  auto task = adbc_from_xptr<RAdbcAsyncTask>(task_xptr);
  int duration_ms = adbc_as_int(duration_ms_sexp);

  if (duration_ms < 0) {
    Rf_error("duration_ms must be >= 0");
  }

  switch (task->status) {
    case RAdbcAsyncTaskStatus::NOT_STARTED:
      return Rf_mkString("not_started");
    case RAdbcAsyncTaskStatus::READY:
      return Rf_mkString("ready");
    default:
      break;
  }

  std::future_status status =
      task->result.wait_for(std::chrono::milliseconds(duration_ms));
  switch (status) {
    case std::future_status::timeout:
      return Rf_mkString("timeout");
    case std::future_status::ready:

      return Rf_mkString("ready");
    default:
      Rf_error("Unknown status returned from future::wait_for()");
  }
}

extern "C" SEXP RAdbcAsyncTaskLaunchSleep(SEXP task_xptr, SEXP duration_ms_sexp) {
  auto task = adbc_from_xptr<RAdbcAsyncTask>(task_xptr);
  error_for_started_task(task);

  int duration_ms = adbc_as_int(duration_ms_sexp);

  task->result = std::async(std::launch::async, [task, duration_ms] {
    std::this_thread::sleep_for(std::chrono::milliseconds(duration_ms));
    *(task->return_code) = ADBC_STATUS_OK;
  });

  task->status = RAdbcAsyncTaskStatus::STARTED;
  return R_NilValue;
}

extern "C" SEXP RAdbcAsyncTaskLaunchExecuteQuery(SEXP task_xptr, SEXP statement_xptr,
                                                 SEXP stream_xptr) {
  auto task = adbc_from_xptr<RAdbcAsyncTask>(task_xptr);
  error_for_started_task(task);

  auto statement = adbc_from_xptr<AdbcStatement>(statement_xptr);
  // auto stream = adbc_from_xptr<ArrowArrayStream>(stream_xptr, /*null_ok*/ true);

  SEXP rows_affected_sexp = PROTECT(Rf_allocVector(REALSXP, 1));
  double* rows_affected_dbl = REAL(rows_affected_sexp);

  task->result = std::async(std::launch::async, [task, statement, rows_affected_dbl] {
    int64_t rows_affected = -1;
    *(task->return_code) =
        AdbcStatementExecuteQuery(statement, nullptr, &rows_affected, task->return_error);
    *rows_affected_dbl = static_cast<double>(rows_affected);
  });

  task->status = RAdbcAsyncTaskStatus::STARTED;
  UNPROTECT(1);
  return rows_affected_sexp;
}