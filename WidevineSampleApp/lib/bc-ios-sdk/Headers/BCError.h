//
//  BCError.h
//  BCiOSLibrary
//
//  Created by Jim R. Wilson on 6/19/12.
//  Copyright (c) 2012 Brightcove. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BCError : NSError

/**
 * Designated initializer, create a BCError with the specified code and info.
 */
- (id)initWithCode:(NSInteger)code userInfo:(NSDictionary *)dict;

/**
 * Convenience initializer, create a BCError with the specified code and message.
 */
- (id)initWithCode:(NSInteger)code message:(NSString *)message;

/**
 * Create a BCError with the specified code and info.
 */
+ (id)errorWithCode:(NSInteger)code userInfo:(NSDictionary *)dict;

/**
 * Create a BCError with the specified code and message.
 */
+ (id)errorWithCode:(NSInteger)code message:(NSString *)message;

@end

/**
 * domain for errors
 */
extern NSString* const BCErrorDomain;

/**
 * error codes.
 */
extern NSInteger const BCErrorCodeCatalogRequestError;
