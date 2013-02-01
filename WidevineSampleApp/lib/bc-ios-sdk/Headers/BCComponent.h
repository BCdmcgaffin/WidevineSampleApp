//
//  BCComponent.h
//  iOS-SDK-Sample-APP
//
//  Created by Keith Peters on 5/1/12.
//  Copyright (c) 2012 Brightcove. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BCEventEmitter.h"
@class BCRegisteringEventEmitter;

/**
 * Base class for all visual and non-visual components
 */
@interface BCComponent : NSObject 
{
    BCRegisteringEventEmitter *emitter;
}

///---------------------------------------------------------------------------------------
/// @name Creating a Component
///---------------------------------------------------------------------------------------

/**
 * Designated initializer. Initializes the component with the given emitter.
 * 
 * @param eventEmitter The upstream event emitter through which this component 
 * instance will communicate.
 * @return Returns the initialized component object.
 */
- (id)initWithEventEmitter:(id<BCEventEmitterProtocol>)eventEmitter;

///---------------------------------------------------------------------------------------
/// @name Allowed Events
///---------------------------------------------------------------------------------------

/**
 * Class method that returns an array of events that this component will be
 * allowed to emit.
 *
 * @return Returns an array of strings representing which events this component 
 * is allowed to emit.
 */
+ (NSArray *)allowedEmits;

/**
 * Class method that returns an array of events that this component will be
 * allowed to listen for.
 * 
 * @return Returns an array of strings representing which events this component 
 * is allowed to listen for.
 */
+ (NSArray *)allowedListeners;

///---------------------------------------------------------------------------------------
/// @name Component Properties
///---------------------------------------------------------------------------------------

/**
 * Returns the registering event emitter that will emit events for this component.
 */
@property (readonly) BCRegisteringEventEmitter *emitter;

///---------------------------------------------------------------------------------------
/// @name Other Methods
///---------------------------------------------------------------------------------------

/**
 * Adds event listeners to the event emitter. Automatically called from init.
 * Should not be called directly.
 */
- (void)setupEventListeners;

/**
 * Emits the given event with given details. Internally this is designated to
 * the component's registering event emitter, which validates the event type
 * before sending the event on to the main emitter.
 */
- (void)emit:(NSString*)type withDetails:(NSDictionary *)details;

@end
