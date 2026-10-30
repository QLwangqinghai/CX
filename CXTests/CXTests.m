//
//  CXTests.m
//  CXTests
//
//  Created by vector on 2026/10/29.
//

#import <XCTest/XCTest.h>
#import "CXCase.h"

@interface CXTests : XCTestCase

@end

@implementation CXTests

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)testExample {
    
    CXCaseRun();
    
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
