//
//  BCMediaService.h
//  BCiOSLibrary
//
//  Created by Keith Peters on 5/10/12.
//  Copyright (c) 2012 Brightcove. All rights reserved.
//

#import "BCComponent.h"
@class BCEvent;
@class BCPlaylist;
@class BCVideo;

@protocol NSURLConnectionDataDelegate;

/**
 * A component that access the Brightcove Media API for finding videos and playlists.
 */
@interface BCMediaService : BCComponent <NSURLConnectionDataDelegate>
{
    NSMutableData *receivedData;
    NSURLConnection *connection;
    SEL connectionLoadedHandler;
    NSString *apiKey;
}

/**
 * Initialize a new media service object with the specified event emitter. This 
 * version of the constructor allows you to optionally specify a URL for the 
 * media API to use. Developers who are not using Brightcove in Japan probably 
 * want to use the version of this method that does not have a base URL 
 * parameter instead.
 *
 * @param eventEmitter the event emitter to listend and respond to events on
 * @param token the API token to use for requests.
 * @param the base URL of the media API to use. Optional.
 * @param an initialized media service object
 */
- (id)initWithEventEmitter:(BCEventEmitter *)eventEmitter token:(NSString *)token baseURL:(NSString *)baseURL;

/**
 * The data received from the server.
 */
@property (nonatomic, retain) NSMutableData *receivedData;

/**
 * API key required to access the api.
 */
@property (nonatomic, retain) NSString *apiKey;

/**
 * The base URL for the Video Cloud Media API. By default, this is set to
 * https://api.brightcove.com/services/library.
 */
@property (nonatomic, readonly) NSString *baseURL;

/**
 * The NSURLConnection used to call the BC API.
 */
@property (nonatomic, retain) NSURLConnection *connection;

/**
 * Callback for @"findVideo" event. Initializes service call to find a video.
 */
- (void)onFindVideo:(BCEvent *)event;

/**
 * Callback for @"findPlaylist" event. Initializes service call to find a playlist.
 */
- (void)onFindPlaylist:(BCEvent *)event;

/**
 * Returns an NSURLConnection to use with the api. Exposed here so it can be mocked in tests.
 */
- (NSURLConnection *)getConnectionWithRequest:(NSURLRequest *)request delegate:(id)delegate;

/**
 * Returns an NSDictionary containing the parsed JSON response from self.receivedData
 */
- (NSDictionary *)getLoadedJSON;

/**
 * Returns a BCVideo based on an NSDictonary which was derived from a json response.
 */
- (BCVideo *)makeVideoWithJSON:(NSDictionary *)json;

/**
 * Returns a BCPlaylist based on an NSDictonary which was derived from a json response.
 */
- (BCPlaylist *)makePlaylistWithJSON:(NSDictionary *)json;

@end
