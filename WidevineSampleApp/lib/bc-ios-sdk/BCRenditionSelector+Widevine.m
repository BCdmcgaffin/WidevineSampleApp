//
//  BCWidevineRenditionSelector.m
//  WidevinePlugin
//
//  Created by David McGaffin on 9/17/12.
//
//

#import <objc/runtime.h>

#import "BCRenditionSelector+Widevine.h"
#import "BCVideo.h"
#import "BCRendition.h"
#import "BCRenditionSet.h"
#import "BCEvent.h"
#import "BCRegisteringEventEmitter.h"
#import "BCPlayerItem.h"

#import "WViPhoneAPI.h"

#define WVError_TransformerUnsupportedConfiguration 4201

@implementation BCRenditionSelector (Widevine)

- (BCRendition *)selectFirstRendition:(BCVideo *)video
{
    BCRenditionSet *renditionSet = [video.renditionSets objectAtIndex:0];
    BCRendition *rendition = [renditionSet.renditions objectAtIndex:0];
    NSURL *widevineUrl = [rendition.properties objectForKey:@"url"];
    NSString *widevineUrlStr = [widevineUrl absoluteString];
    
    NSLog(@"%s Rendition URL: '%@'", __PRETTY_FUNCTION__, widevineUrlStr);
    
    if ([self isWidevineRendition:widevineUrlStr]) {
        WViOsApiStatus status = WV_QueryAssetStatus(widevineUrlStr);
        if (status == WViOsApiStatus_OK) {
            NSMutableString *responseUrl = [NSMutableString string];
            status = WV_Play(widevineUrlStr, responseUrl, 0);
            
            switch (status) {
                case WViOsApiStatus_OK:
                    rendition = [[[BCRendition alloc] initWithURL: [NSURL URLWithString:responseUrl]] autorelease];
                    break;
                case WViOsApiStatus_AlreadyPlaying:
                    // The rendition cannot be changed because WV_Play() can only manage one video at a time
                    // and it is already playing this video or another one.
                    break;
                    
                default:
                    // The rendition will not play, but we return it from this method because
                    // the iOS-SDK expects a non-nil value.
                    NSLog(@"    Unexpected WViOsApiStatus %d for URL of rendition '%@'; This means that the rendition might not play.", status, rendition);
                    break;
            }
        }
    }
    
    return rendition;
}

- (BOOL)isWidevineRendition:(NSString *)url
{
    return [url rangeOfString:@".wvm"].location != NSNotFound;
}
@end