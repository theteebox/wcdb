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

import Foundation
public final class LiteralValue : Describable {
    public init(_ value: Int32) {
        super.init(String(value))
    }
    
    public init(_ value: Int64) {
        super.init(String(value))
    }
    
    public init(_ value: Bool) {
        super.init(String(value))
    }

    public init(_ value: Double) {
        super.init(String(value))
    }

    public override init(_ value: String) {
        super.init("'\(value.replacingOccurrences(of: "'", with: "''"))'")
    }
    
    public init(_ value: Data) {
        let string = String(data: value, encoding: .utf8) ?? ""
        super.init("'\(string.replacingOccurrences(of: "'", with: "''"))'")
    }
    
    public init(_ value: Void?) {
        super.init("NULL")
    }

    public convenience init<ColumnEncodableType: ColumnEncodable>(_ columnEncodableValue: ColumnEncodableType) {
        if let value = columnEncodableValue.archivedFundamentalValue() {
            switch ColumnEncodableType.columnType {
            case .Integer32:
                if let int32Value = value as? Int32 {
                    self.init(int32Value)
                }else {
                    self.init(nil)
                }
            case .Integer64:
                if let int64Value = value as? Int64 {
                    self.init(int64Value)
                }else {
                    self.init(nil)
                }
            case .Float:
                if let doubleValue = value as? Double {
                    self.init(doubleValue)
                }else {
                    self.init(nil)
                }
            case .Text:
                if let stringValue = value as? String {
                    self.init(stringValue)
                }else {
                    self.init(nil)
                }
            case .BLOB:
                if let dataValue = value as? Data {
                    self.init(dataValue)
                }else {
                    self.init(nil)
                }
            default: 
                self.init(nil)
            }
        }else {
            self.init(nil)
        }
    }
}

extension LiteralValue: ExpressibleByNilLiteral {
    public convenience init(nilLiteral: ()) {
        self.init(nilLiteral)
    }
}

extension LiteralValue: ExpressibleByIntegerLiteral {
    public convenience init(integerLiteral value: Int) {
        self.init(value)
    }
}

extension LiteralValue: ExpressibleByBooleanLiteral {
    public convenience init(booleanLiteral value: Bool) {
        self.init(value)
    }
}

extension LiteralValue: ExpressibleByFloatLiteral {
    public convenience init(floatLiteral value: Double) {
        self.init(value)
    }
}

extension LiteralValue: ExpressibleByStringLiteral {
    public convenience init(stringLiteral value: String) {
        self.init(value)
    }
}

extension LiteralValue: LiteralValueConvertible {
    public func asLiteralValue() -> LiteralValue {
        return self
    }
}
