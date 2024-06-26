﻿/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

using Apache.Arrow.C;

namespace Apache.Arrow.Adbc.C
{
    internal unsafe delegate void ErrorRelease(CAdbcError* error);
    internal unsafe delegate AdbcStatusCode DatabaseFn(CAdbcDatabase* database, CAdbcError* error);
    internal unsafe delegate AdbcStatusCode ConnectionFn(CAdbcConnection* connection, CAdbcError* error);

#if !NET5_0_OR_GREATER
    internal unsafe delegate AdbcStatusCode DriverRelease(CAdbcDriver* driver, CAdbcError* error);
    internal unsafe delegate void PartitionsRelease(CAdbcPartitions* partitions);
    internal unsafe delegate AdbcStatusCode DatabaseSetOption(CAdbcDatabase* database, byte* name, byte* value, CAdbcError* error);
    internal unsafe delegate AdbcStatusCode ConnectionGetObjects(CAdbcConnection* connection, int depth, byte* catalog, byte* db_schema, byte* table_name, byte** table_type, byte* column_name, CArrowArrayStream* stream, CAdbcError* error);
    internal unsafe delegate AdbcStatusCode ConnectionGetTableSchema(CAdbcConnection* connection, byte* catalog, byte* db_schema, byte* table_name, CArrowSchema* schema, CAdbcError* error);
    internal unsafe delegate AdbcStatusCode ConnectionGetTableTypes(CAdbcConnection* connection, CArrowArrayStream* stream, CAdbcError* error);
    internal unsafe delegate AdbcStatusCode ConnectionInit(CAdbcConnection* connection, CAdbcDatabase* database, CAdbcError* error);
    internal unsafe delegate AdbcStatusCode ConnectionGetInfo(CAdbcConnection* connection, int* info_codes, int info_codes_length, CArrowArrayStream* stream, CAdbcError* error);
    internal unsafe delegate AdbcStatusCode ConnectionReadPartition(CAdbcConnection* connection, byte* serialized_partition, int serialized_length, CArrowArrayStream* stream, CAdbcError* error);
    internal unsafe delegate AdbcStatusCode ConnectionSetOption(CAdbcConnection* connection, byte* name, byte* value, CAdbcError* error);
    internal unsafe delegate AdbcStatusCode StatementBind(CAdbcStatement* statement, CArrowArray* array, CArrowSchema* schema, CAdbcError* error);
    internal unsafe delegate AdbcStatusCode StatementBindStream(CAdbcStatement* statement, CArrowArrayStream* stream, CAdbcError* error);
    internal unsafe delegate AdbcStatusCode StatementExecuteQuery(CAdbcStatement* statement, CArrowArrayStream* stream, long* rows, CAdbcError* error);
    internal unsafe delegate AdbcStatusCode StatementExecutePartitions(CAdbcStatement* statement, CArrowSchema* schema, CAdbcPartitions* partitions, long* rows, CAdbcError* error);
    internal unsafe delegate AdbcStatusCode StatementNew(CAdbcConnection* connection, CAdbcStatement* statement, CAdbcError* error);
    internal unsafe delegate AdbcStatusCode StatementFn(CAdbcStatement* statement, CAdbcError* error);
    internal unsafe delegate AdbcStatusCode StatementSetSqlQuery(CAdbcStatement* statement, byte* text, CAdbcError* error);
    internal unsafe delegate AdbcStatusCode StatementSetSubstraitPlan(CAdbcStatement* statement, byte* plan, int length, CAdbcError* error);
    internal unsafe delegate AdbcStatusCode StatementGetParameterSchema(CAdbcStatement* statement, CArrowSchema* schema, CAdbcError* error);
#endif
}
