//
//  BCCatalog.h
//  BCiOSLibrary
//
//  Created by David LaPalomento on 6/15/12.
//  Copyright (c) 2012 Brightcove. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BCError.h"
#import "BCEventEmitter.h"
#import "BCMediaService.h"

/**
 * The type of callback blocks for catalog methods which find videos.
 * @param error instance of BCError if an error occurred, or nil if successful.
 * @param video instance of BCVideo if successful, or nil if an error occurred.
 */
typedef void (^BCVideoResponseBlock)(BCError *error, BCVideo *video);

/**
 * The type of callback blocks for catalog methods which find playlists.
 * @param error instance of BCError if an error occurred, or nil if successful.
 * @param playlist instance of BCPlaylist if successful, or nil if an error 
 * occurred.
 */
typedef void (^BCPlaylistResponseBlock)(BCError *error, BCPlaylist *playlist);

/**
 * The BCCatalog class provides asynchronous methods for retrieving information 
 * about videos and playlists from Brightcove’s Media API services.
 *
 * To accept a callback for the asynchronous API response, methods of BCCatalog 
 * implement the observer/selector pattern.  This pattern is commonly applied in
 * Objective-C development to capture an object/method pair for later callback.
 *
 * Network requests such as those implemented by the BCCatalog class sometimes 
 * fail.  If the request succeeds, the observer’s selector will be invoked with 
 * nil for the first parameter and a BCVideo object for the second.  If an error
 * occurs during the execution of the request, the specified observer’s selector
 * will be invoked with an error object as the first parameter and nil as the 
 * second parameter.
 *
 * Only one request can be in-flight per BCCatalog at any point in time.
 */
@interface BCCatalog : NSObject
{
    BCEventEmitter *emitter;
    id responseObserver;
    SEL responseSelector;
}

///-----------------------------------------------------------------------------
/// @name Creating the Catalog
///-----------------------------------------------------------------------------

/**
 * Designated initializer, returns a BCCatalog object initialized with the 
 * specified token.
 *
 * To prevent unauthorized access to the metadata in your account, Video Cloud 
 * protects access to the API with tokens that you pass as parameters when 
 * making API calls. Like other web-based APIs, tokens are generated for you by 
 * Video Cloud and protected by you.
 * @param token string containing your Video Cloud Media API token.
 * @return an initialized BCCatalog
 */
- (id)initWithToken:(NSString *)token;

/**
 * Returns a BCCatalog object initialized with the specified token. The second 
 * argument specifies the URL of the media API to send requests to. If it is 
 * nil, https://api.brightcove.com/services/library is used.
 *
 * To prevent unauthorized access to the metadata in your account, Video Cloud
 * protects access to the API with tokens that you pass as parameters when
 * making API calls. Like other web-based APIs, tokens are generated for you by
 * Video Cloud and protected by you.
 * @param token string containing your Video Cloud Media API token.
 * @param baseURL the URL to prepend to all media API requests. Optional.
 * @return an initialized BCCatalog
 */
- (id)initWithToken:(NSString *)token baseURL:(NSString *)baseURL;

/**
 * Factory initializer, returns a BCCatalog object initialized with the 
 * specified token.
 *
 * To prevent unauthorized access to the metadata in your account, Video Cloud 
 * protects access to the API with tokens that you pass as parameters when 
 * making API calls. Like other web-based APIs, tokens are generated for you by 
 * Video Cloud and protected by you.
 * @param token string containing your Video Cloud Media API token.
 * @return an initialized BCCatalog
 */
+ (id)catalogWithToken:(NSString *)token;

/**
 * Factory initializer, returns a BCCatalog object initialized with the
 * specified token. The second argument specifies the URL of the media API to 
 * send requests to. If it is nil, https://api.brightcove.com/services/library 
 * is used.
 *
 * To prevent unauthorized access to the metadata in your account, Video Cloud
 * protects access to the API with tokens that you pass as parameters when
 * making API calls. Like other web-based APIs, tokens are generated for you by
 * Video Cloud and protected by you.
 * @param token string containing your Video Cloud Media API token.
 * @param baseURL the URL to prepend to all media API requests. Optional.
 * @return an initialized BCCatalog
 */
+ (id)catalogWithToken:(NSString *)token baseURL:baseURL;

///-----------------------------------------------------------------------------
/// @name Looking Up Videos
///-----------------------------------------------------------------------------

/**
 * Retrieves a BCVideo from the Media API service by its video ID, then invokes 
 * the provided block.
 * 
 * @param videoID string containing the ID of the video to find.
 * @param options Additional NSString query parameters to add to the Media API 
 * requests. These values will override the default values if they conflict.
 * @param responseBlock block which will be invoked when the request finishes.
 */
- (void)findVideoByID:(NSString *)videoID options:(NSDictionary *)options callBlock:(BCVideoResponseBlock)responseBlock;

/**
 * Retrieves a BCVideo from the Media API service by its reference ID -- a 
 * customer supplied unique identifier.
 * 
 * @param referenceID string containing the reference ID of the video to find.
 * @param options Additional NSString query parameters to add to the Media API
 * requests. These values will override the default values if they conflict.
 * @param responseBlock block which will be invoked when the request finishes.
 */
- (void)findVideoByReferenceID:(NSString *)referenceID options:(NSDictionary *)options callBlock:(BCVideoResponseBlock)responseBlock;

/**
 * Retrieves a BCVideo from the Media API service by its video ID.
 * 
 * Like all observer/selector methods of BCCatalog, this method will invoke the 
 * selector with an error object as the first parameter if an error occurred, or
 * nil if the request succeeded.
 * @param videoID string containing the ID of the video to find.
 * @param observer object registering as the observer for the asynchronous 
 * response -- must not be nil
 * @param selector selector that specifies the message sent to the observer when
 * a response is available. 
 */
- (void)findVideoByID:(NSString *)videoID withObserver:(id)observer selector:(SEL)selector;

/**
 * Retrieves a BCVideo from the Media API service by its reference ID---a 
 * customer supplied unique identifier.
 * 
 * Like all observer/selector methods of BCCatalog, this method will invoke the 
 * selector with an error object as the first parameter if an error occurred, or
 * nil if the request succeeded.
 * @param referenceID string containing the reference ID of the video to find.
 * @param observer object registering as the observer for the asynchronous 
 * response---must not be nil.
 * @param selector selector that specifies the message sent to the observer when
 * a response is available.
 */
- (void)findVideoByReferenceID:(NSString *)referenceID withObserver:(id)observer selector:(SEL)selector;

///-----------------------------------------------------------------------------
/// @name Looking Up Playlists
///-----------------------------------------------------------------------------

/**
 * Retrieves a BCPlaylist from the Media API service by its playlist ID.
 *
 * @param playlistID string containing the ID of the playlist to find.
 * @param options Additional NSString query parameters to add to the Media API
 * requests. These values will override the default values if they conflict.
 * @param responseBlock block which will be invoked when the request finishes.
 */
- (void)findPlaylistByID:(NSString *)playlistID options:(NSDictionary *)options callBlock:(BCPlaylistResponseBlock)responseBlock;

/**
 * Retrieves a BCPlaylist from the Media API service by its reference ID---a 
 * customer supplied unique identifier.
 *
 * @param referenceID string containing the reference ID of the playlist to 
 * find.
 * @param options Additional NSString query parameters to add to the Media API
 * requests. These values will override the default values if they conflict.
 * @param responseBlock block which will be invoked when the request finishes.
 */
- (void)findPlaylistByReferenceID:(NSString *)referenceID options:(NSDictionary *)options callBlock:(BCPlaylistResponseBlock)responseBlock;

/**
 * Retrieves a BCPlaylist from the Media API service by its playlist ID.
 *
 * Like all observer/selector methods of BCCatalog, this method will invoke the 
 * selector with an error object as the first parameter if an error occurred, or
 * nil if the request succeeded.
 * @param playlistID string containing the ID of the playlist to find.
 * @param observer object registering as the observer for the asynchronous 
 * response---must not be nil.
 * @param selector selector that specifies the message sent to the observer when
 * a response is available.
 */
- (void)findPlaylistByID:(NSString *)playlistID withObserver:(id)observer selector:(SEL)selector;

/**
 * Retrieves a BCPlaylist from the Media API service by its reference ID -- a 
 * customer supplied unique identifier.
 *
 * Like all observer/selector methods of BCCatalog, this method will invoke the 
 * selector with an error object as the first parameter if an error occurred, or
 * nil if the request succeeded.
 * @param referenceID string containing the reference ID of the playlist to 
 * find.
 * @param observer object registering as the observer for the asynchronous 
 * response -- must not be nil.
 * @param selector selector that specifies the message sent to the observer when
 * a response is available.
 */
- (void)findPlaylistByReferenceID:(NSString *)referenceID withObserver:(id)observer selector:(SEL)selector;

///-----------------------------------------------------------------------------
/// @name Catalog Properties
///-----------------------------------------------------------------------------

/**
 * The media service component used to manage Media API requests.
 */
@property (nonatomic, retain, readonly) BCMediaService *mediaService;

/**
 * The BCEventEmitter used by the catalog.
 */
@property (nonatomic, retain, readonly) BCEventEmitter *emitter;

@end