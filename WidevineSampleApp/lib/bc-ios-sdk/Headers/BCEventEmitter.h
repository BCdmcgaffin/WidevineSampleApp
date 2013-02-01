//
//  BCEventEmitter.h
//  iOS-SDK-Sample-APP
//
//  Created by Keith Peters on 5/1/12.
//  Copyright (c) 2012 Brightcove. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BCEventEmitterProtocol.h"

/**
 * Main event emitter that receives and emits events. See the BCEventEmitterProtocol 
 * for behavioral details.
 */
@interface BCEventEmitter : NSObject <BCEventEmitterProtocol>

/**
 * Returns a new event emitter.
 */
+ (BCEventEmitter *)emitter;

@end
