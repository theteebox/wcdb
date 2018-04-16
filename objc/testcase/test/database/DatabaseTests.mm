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

#import "TestCase.h"

@interface DatabaseTests : TestCase

@end

@implementation DatabaseTests {
    WCTDatabase *_database;
}

- (void)setUp
{
    [super setUp];

    _database = [[WCTDatabase alloc] initWithPath:self.recommendedPath];
}

- (void)tearDown
{
    [_database close:^{
      XCTAssertTrue([_database removeFiles]);
    }];

    _database = nil;

    [super tearDown];
}

- (void)test_open
{
    XCTAssertFalse([_database isOpened]);
    XCTAssertTrue([_database canOpen]);
    XCTAssertTrue([_database isOpened]);
}

- (void)test_tag
{
    WCTDatabase *database2 = [[WCTDatabase alloc] initWithPath:_database.path];
    _database.tag = rand();
    XCTAssertEqual(_database.tag, database2.tag);
}

- (void)test_existing_tag
{
    _database.tag = rand();
    WCTDatabase *database2 = [[WCTDatabase alloc] initWithExistingTag:_database.tag];
    XCTAssertNotNil(database2);
    XCTAssertTrue([_database.path isEqualToString:database2.path]);
}

- (void)test_blockade
{
    [_database blockade];
    NSDate *main;
    __block NSDate *subthread;
    dispatch_group_t group = dispatch_group_create();
    dispatch_group_async(group, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
      XCTAssertTrue([_database canOpen]);
      @synchronized(self)
      {
          subthread = [NSDate date];
      }
    });
    [NSThread sleepForTimeInterval:3];
    main = [NSDate date];
    [_database unblockade];
    dispatch_group_wait(group, DISPATCH_TIME_FOREVER);
    XCTAssertTrue([main compare:subthread] == NSOrderedAscending);
}

- (void)test_inside_blockade
{
    dispatch_group_t group = dispatch_group_create();
    __block NSDate *main;
    __block NSDate *subthread;
    BOOL result = [_database blockadeUntilDone:^(WCTHandle *handle) {
      XCTAssertTrue([_database isBlockaded]);
      dispatch_group_async(group, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        XCTAssertTrue([_database canOpen]);
        @synchronized(self)
        {
            subthread = [NSDate date];
        }
      });
      [NSThread sleepForTimeInterval:3];
      main = [NSDate date];
    }];
    dispatch_group_wait(group, DISPATCH_TIME_FOREVER);
    XCTAssertTrue([main compare:subthread] == NSOrderedAscending);
    XCTAssertTrue(result);
}

@end