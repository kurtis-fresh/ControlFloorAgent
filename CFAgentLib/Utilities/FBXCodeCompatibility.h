/**
 * Copyright (c) 2015-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <CFAgentLib/CFAgentLib.h>
#import "XCPointerEvent.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Set of categories that patches method name differences between Xcode versions,
 so that WDA can be build with different Xcode versions.
 */
@interface XCElementSnapshot (FBCompatibility)

- (nullable XCElementSnapshot *)fb_rootElement;

+ (nullable SEL)fb_attributesForElementSnapshotKeyPathsSelector;

@end

/**
 The exception happends if one tries to call application method,
 which is not supported in the current iOS version
 */
extern NSString *const FBApplicationMethodNotSupportedException;

@interface XCUIApplication (FBCompatibility)

+ (nullable instancetype)fb_applicationWithPID:(pid_t)processID;

/**
 Get the state of the application. This method only returns reliable results on Xcode SDK 9+

 @return State value as enum item. See https://developer.apple.com/documentation/xctest/xcuiapplicationstate?language=objc for more details.
 */
- (NSUInteger)fb_state;

/**
 Activate the application by restoring it from the background.
 Nothing will happen if the application is already in foreground.
 This method is only supported since Xcode9.

 @throws FBTimeoutException if the app is still not active after the timeout
 */
- (void)fb_activate;

/**
 Terminate the application and wait until it disappears from the list of active apps
 */
- (void)fb_terminate;

@end

@interface XCUIElementQuery (FBCompatibility)

/* Performs short-circuit UI tree traversion in iOS 11+ to get the first element matched by the query. Equals to nil if no matching elements are found */
@property(nullable, readonly) XCUIElement *fb_firstMatch;

/*
 This is the local wrapper for bounded elements extraction.
 It uses either indexed or bounded binding based on the `boundElementsByIndex` configuration
 flag value.
 */
@property(readonly) NSArray<XCUIElement *> *fb_allMatches;

/**
 Returns single unique matching snapshot for the given query

 @param error The error instance if there was a failure while retrieveing the snapshot
 @returns The cached unqiue snapshot or nil if the element is stale
 */
- (nullable XCElementSnapshot *)fb_uniqueSnapshotWithError:(NSError **)error;

/**
 @returns YES if the element supports unique snapshots retrieval
 */
- (BOOL)fb_isUniqueSnapshotSupported;

@end


@interface XCPointerEvent (FBCompatibility)

- (BOOL)fb_areKeyEventsSupported;

@end


@interface XCUIElement (FBCompatibility)

/**
 Enforces snapshot resolution of the destination element.
 !!! Do not cal this method on Xcode 11 or later due to performance considerations.
 Prefer using fb_takeSnapshot instead.

 @param error Contains the actual error if element resolution fails
 @returns YES if the element has been successfully resolved
 */
- (BOOL)fb_resolveWithError:(NSError **)error;

/**
 Determines whether current iOS SDK supports non modal elements inlusion into snapshots

 @return Either YES or NO
 */
+ (BOOL)fb_supportsNonModalElementsInclusion;

/**
 Retrieves element query

 @return Element query property extended with non modal elements depending on the actual configuration
 */
- (XCUIElementQuery *)fb_query;

@end

NS_ASSUME_NONNULL_END
