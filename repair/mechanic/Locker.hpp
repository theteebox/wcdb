/*
 * Tencent is pleased to support the open source community by making
 * WCDB available.
 *
 * Copyright (C) 2017 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *       https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _WCDB_LOCKER_HPP
#define _WCDB_LOCKER_HPP

#include <WCDB/String.hpp>

namespace WCDB {

class Error;

namespace Repair {

class Locker {
public:
    virtual ~Locker();
    virtual void setPath(const String &path) = 0;
    virtual const String &getPath() const = 0;
    virtual const Error &getError() const = 0;

    virtual bool acquireLock() = 0;
    virtual bool releaseLock() = 0;
};

class ReadLocker : public Locker {
public:
    virtual ~ReadLocker();
};
class WriteLocker : public Locker {
public:
    virtual ~WriteLocker();
};

class LockerHolder {
public:
    LockerHolder();
    virtual ~LockerHolder();
    void setReadLocker(ReadLocker *readLocker);
    void setWriteLocker(WriteLocker *writeLocker);

protected:
    ReadLocker *m_readLocker;
    WriteLocker *m_writeLocker;
};

} //namespace Repair

} //namespace WCDB

#endif /* _WCDB_LOCKER_HPP */
