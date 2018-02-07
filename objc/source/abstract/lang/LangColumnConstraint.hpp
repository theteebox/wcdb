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

#ifndef LangColumnConstraint_hpp
#define LangColumnConstraint_hpp

#include <WCDB/lang_common.h>

class LangColumnConstraint : public Lang {
public:
    copy_on_write_string name;
    enum class Type : int {
        PrimaryKey,
        NotNull,
        Unique,
        Check,
        Default,
        Collate,
        ForeignKeyClause,
    };
    Type type;

    LangOrder order;

    LangConflictClause conflictClause;
    bool autoIncrement;

    copy_on_write_lazy_lang<LangExpr> expr;

    enum class DefaultSwitch {
        LiteralValue,
        Expr,
    };
    DefaultSwitch defaultSwitcher;
    copy_on_write_lazy_lang<LangLiteralValue> literalValue;

    copy_on_write_string collationName;

    copy_on_write_lazy_lang<LangForeignKeyClause> foreignKeyClause;

    virtual copy_on_write_string SQL() const override;
};

#endif /* LangColumnConstraint_hpp */