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

#include <WCDB/lang.h>
#include <WCDB/utility.hpp>

copy_on_write_string LangLiteralValue::SQL() const
{
    std::string description;
    switch (type) {
        case Type::NumbericInteger:
            description.append(std::to_string(integerValue));
            break;
        case Type::NumbericFloat:
            description.append(std::to_string(floatValue));
            break;
        case Type::BLOB:
            description.append(
                LangLiteralValue::stringByAntiInjecting(dataValue.get()));
            break;
        case Type::String:
            description.append(
                LangLiteralValue::stringByAntiInjecting(stringValue.get()));
            break;
        case Type::Null:
            description.append("NULL");
            break;
        case Type::CurrentTime:
            description.append("CURRENT_TIME");
            break;
        case Type::CurrentDate:
            description.append("CURRENT_DATE");
            break;
        case Type::CurrentTimestamp:
            description.append("CURRENT_TIMESTAMP");
            break;
    }
    return description;
}

std::string LangLiteralValue::stringByAntiInjecting(const std::string &origin)
{
    return "'" + stringByReplacingOccurrencesOfString(origin, "'", "''") + "'";
}

std::string LangLiteralValue::stringByAntiInjecting(
    const std::vector<unsigned char> &origin)
{
    std::string str(origin.begin(), origin.end());
    return "'" + stringByReplacingOccurrencesOfString(str, "'", "''") + "'";
}