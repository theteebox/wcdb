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

#ifndef _WCDB_CELL_HPP
#define _WCDB_CELL_HPP

#include <WCDB/Initializeable.hpp>
#include <WCDB/MappedData.hpp>
#include <WCDB/PagerRelated.hpp>
#include <WCDB/Serialization.hpp>

namespace WCDB {

namespace Repair {

class Page;

class Cell final : public PagerRelated, public Initializeable {
public:
    Cell(int pointer, Page *page, Pager *pager);

    const Page &getPage() const;

    enum Type {
        Null = 0,
        Integer = 1,
        Real = 2,
        Text = 3,
        BLOB = 4,
    };
    int64_t getRowID() const;
    Type getValueType(int index) const;
    int getCount() const;

    int64_t integerValue(int index) const;
    double doubleValue(int index) const;
    UnsafeString textValue(int index) const;
    String stringValue(int index) const;
    const UnsafeData blobValue(int index) const;

protected:
    static int getLengthOfSerialType(int serialType);
    static int isSerialTypeSanity(int serialType);

    Page *m_page;

    int64_t m_rowid;
    int m_pointer;

    Deserialization m_deserialization;
    Data m_overflowedPayloadHolder;
    MappedData m_nonOverflowedPayloadHolder;
    UnsafeData m_payload;
    //serial type -> offset of value
    std::vector<std::pair<int, int>> m_columns;

#pragma mark - Initializeable
protected:
    bool doInitialize() override final;
};

} //namespace Repair

} //namespace WCDB

#endif /* _WCDB_CELL_HPP */
