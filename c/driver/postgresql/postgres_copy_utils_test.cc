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

#include <gtest/gtest.h>
#include <nanoarrow/nanoarrow.h>

#include "postgres_copy_utils.h"

// COPY (SELECT CAST("col" AS BOOLEAN) AS "col" FROM (  VALUES (TRUE), (FALSE), (NULL)) AS
// drvd("col")) TO STDOUT;
static uint8_t kTestPgCopyBoolean[] = {
    0x50, 0x47, 0x43, 0x4f, 0x50, 0x59, 0x0a, 0xff, 0x0d, 0x0a, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

TEST(PostgresCopyUtilsTest, PostgresCopyReadBoolean) {
  EXPECT_EQ(sizeof(kTestPgCopyBoolean), sizeof(kTestPgCopyBoolean));
}

// COPY (SELECT CAST("col" AS SMALLINT) AS "col" FROM (  VALUES (-123), (-1), (1), (123),
// (NULL)) AS drvd("col")) TO STDOUT WITH (FORMAT binary);
static uint8_t kTestPgCopySmallInt[] = {
    0x50, 0x47, 0x43, 0x4f, 0x50, 0x59, 0x0a, 0xff, 0x0d, 0x0a, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x02, 0xff, 0x85, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0xff, 0xff, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x7b, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

TEST(PostgresCopyUtilsTest, PostgresCopyReadSmallInt) {
  EXPECT_EQ(sizeof(kTestPgCopySmallInt), sizeof(kTestPgCopySmallInt));
}

// COPY (SELECT CAST("col" AS INTEGER) AS "col" FROM (  VALUES (-123), (-1), (1), (123),
// (NULL)) AS drvd("col")) TO STDOUT WITH (FORMAT binary);
static uint8_t kTestPgCopyInteger[] = {
    0x50, 0x47, 0x43, 0x4f, 0x50, 0x59, 0x0a, 0xff, 0x0d, 0x0a, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0xff, 0xff, 0xff,
    0x85, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0xff, 0xff, 0xff, 0xff, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00,
    0x00, 0x00, 0x7b, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

TEST(PostgresCopyUtilsTest, PostgresCopyReadInteger) {
  EXPECT_EQ(sizeof(kTestPgCopyInteger), sizeof(kTestPgCopyInteger));
}

// COPY (SELECT CAST("col" AS BIGINT) AS "col" FROM (  VALUES (-123), (-1), (1), (123),
// (NULL)) AS drvd("col")) TO STDOUT WITH (FORMAT binary);
static uint8_t kTestPgCopyBigInt[] = {
    0x50, 0x47, 0x43, 0x4f, 0x50, 0x59, 0x0a, 0xff, 0x0d, 0x0a, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x85, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x7b, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

TEST(PostgresCopyUtilsTest, PostgresCopyReadBigInt) {
  EXPECT_EQ(sizeof(kTestPgCopyBigInt), sizeof(kTestPgCopyBigInt));
}

// COPY (SELECT CAST("col" AS REAL) AS "col" FROM (  VALUES (-123.456), (-1), (1),
// (123.456), (NULL)) AS drvd("col")) TO STDOUT WITH (FORMAT binary);
static uint8_t kTestPgCopyReal[] = {
    0x50, 0x47, 0x43, 0x4f, 0x50, 0x59, 0x0a, 0xff, 0x0d, 0x0a, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0xc2, 0xf6, 0xe9,
    0x79, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0xbf, 0x80, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x04, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x42,
    0xf6, 0xe9, 0x79, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

TEST(PostgresCopyUtilsTest, PostgresCopyReadReal) {
  EXPECT_EQ(sizeof(kTestPgCopyReal), sizeof(kTestPgCopyReal));
}

// COPY (SELECT CAST("col" AS DOUBLE PRECISION) AS "col" FROM (  VALUES (-123.456), (-1),
// (1), (123.456), (NULL)) AS drvd("col")) TO STDOUT WITH (FORMAT binary);
static uint8_t kTestPgCopyDoublePrecision[] = {
    0x50, 0x47, 0x43, 0x4f, 0x50, 0x59, 0x0a, 0xff, 0x0d, 0x0a, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0xc0, 0x5e, 0xdd,
    0x2f, 0x1a, 0x9f, 0xbe, 0x77, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0xbf, 0xf0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x3f, 0xf0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x40, 0x5e, 0xdd,
    0x2f, 0x1a, 0x9f, 0xbe, 0x77, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

TEST(PostgresCopyUtilsTest, PostgresCopyReadDoublePrecision) {
  EXPECT_EQ(sizeof(kTestPgCopyDoublePrecision), sizeof(kTestPgCopyDoublePrecision));
}

// COPY (SELECT CAST("col" AS TEXT) AS "col" FROM (  VALUES ('abc'), ('1234'),
// (NULL::text)) AS drvd("col")) TO STDOUT WITH (FORMAT binary);
static uint8_t kTestPgCopyText[] = {
    0x50, 0x47, 0x43, 0x4f, 0x50, 0x59, 0x0a, 0xff, 0x0d, 0x0a, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x03, 0x61, 0x62, 0x63, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x31, 0x32,
    0x33, 0x34, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

TEST(PostgresCopyUtilsTest, PostgresCopyReadText) {
  EXPECT_EQ(sizeof(kTestPgCopyText), sizeof(kTestPgCopyText));
}

// COPY (SELECT CAST("col" AS INTEGER ARRAY) AS "col" FROM (  VALUES ('{-123, -1}'), ('{0,
// 1, 123}'), (NULL)) AS drvd("col")) TO STDOUT WITH (FORMAT binary);
static uint8_t kTestPgCopyIntegerArray[] = {
    0x50, 0x47, 0x43, 0x4f, 0x50, 0x59, 0x0a, 0xff, 0x0d, 0x0a, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x02, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0xff, 0xff, 0xff, 0x85, 0x00, 0x00, 0x00,
    0x04, 0xff, 0xff, 0xff, 0xff, 0x00, 0x01, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x03, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x7b, 0x00,
    0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

TEST(PostgresCopyUtilsTest, PostgresCopyReadArray) {
  EXPECT_EQ(sizeof(kTestPgCopyIntegerArray), sizeof(kTestPgCopyIntegerArray));
}

// CREATE TYPE custom_record AS (nested1 integer, nested2 double precision);
// COPY (SELECT CAST("col" AS custom_record) AS "col" FROM (  VALUES ('(123, 456.789)'),
// ('(12, 345.678)'), (NULL)) AS drvd("col")) TO STDOUT WITH (FORMAT binary);
static uint8_t kTestPgCopyCustomRecord[] = {
    0x50, 0x47, 0x43, 0x4f, 0x50, 0x59, 0x0a, 0xff, 0x0d, 0x0a, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x20, 0x00,
    0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00,
    0x00, 0x7b, 0x00, 0x00, 0x02, 0xbd, 0x00, 0x00, 0x00, 0x08, 0x40, 0x7c, 0x8c,
    0x9f, 0xbe, 0x76, 0xc8, 0xb4, 0x00, 0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00,
    0x00, 0x02, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x02, 0xbd, 0x00, 0x00, 0x00, 0x08, 0x40, 0x75, 0x9a, 0xd9,
    0x16, 0x87, 0x2b, 0x02, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

TEST(PostgresCopyUtilsTest, PostgresCopyReadCustomRecord) {
  EXPECT_EQ(sizeof(kTestPgCopyCustomRecord), sizeof(kTestPgCopyCustomRecord));
}