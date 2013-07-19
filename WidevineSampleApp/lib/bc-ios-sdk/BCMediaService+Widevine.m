//
//  BCMediaService+Widevine.m
//  WidevinePlugin
//
//  Created by David McGaffin on 1/21/13.
//
//

#import "BCMediaService+Widevine.h"
#import "BCRendition.h"
#import "BCVideo.h"
#import "BCRenditionSet.h"

@implementation BCMediaService (Widevine)

/**
 * This override is necessary because it is the only way to populate a BCVideo with the contents of the 
 * WVMRenditions property returned from the media api call.
 */
- (BCVideo *)makeVideoWithJSON:(NSDictionary *)json
{
    NSMutableDictionary *properties = [[NSMutableDictionary alloc] init];
    NSDictionary *wvmRendition = nil;
    
    // Checking !=NULL, !=Nil, isEqual:Nil are not sufficient for JSON or dictionary objects.
    if([json objectForKey:@"WVMRenditions"] && ![[json objectForKey:@"WVMRenditions"] isEqual:[NSNull null]]) {
        NSArray *wvmRenditions = (NSArray *) [json objectForKey:@"WVMRenditions"];
        [properties setValue:wvmRenditions forKey:@"WVMRenditions"];
        
        if ([wvmRenditions count] > 0) {
            wvmRendition = [wvmRenditions objectAtIndex:0];
            [properties setValue:[wvmRendition objectForKey:@"videoDuration"] forKey:@"duration"];
        }
    }
    if ([json objectForKey:@"videoStillURL"] && ![[json objectForKey:@"videoStillURL"] isEqual:[NSNull null]]) {
        [properties setValue:[NSURL URLWithString:[json objectForKey:@"videoStillURL"]] forKey:@"videoStillURL"];
    }
    if ([json objectForKey:@"name"] && ![[json objectForKey:@"name"] isEqual:[NSNull null]]) {
        [properties setValue:[json objectForKey:@"name"] forKey:@"name"];
    }
    if ([json objectForKey:@"shortDescription"] && ![[json objectForKey:@"shortDescription"] isEqual:[NSNull null]]) {
        [properties setValue:[json objectForKey:@"shortDescription"] forKey:@"shortDescription"];
    }
    if ([json objectForKey:@"referenceId"] && ![[json objectForKey:@"referenceId"] isEqual:[NSNull null]]) {
        [properties setValue:[NSString stringWithFormat:@"%@", [json objectForKey:@"referenceId"]] forKey:@"referenceID"];
    }
    if ([json objectForKey:@"id"] && ![[json objectForKey:@"id"] isEqual:[NSNull null]]) {
        [properties setValue:[NSString stringWithFormat:@"%@", [json objectForKey:@"id"]] forKey:@"videoID"];
    }
    if ([json objectForKey:@"customFields"] && ![[json objectForKey:@"customFields"] isEqual:[NSNull null]]) {
        [properties setValue:[json objectForKey:@"customFields"] forKey:@"customFields"];
    }
    if ([json objectForKey:@"pubID"] && ![[json objectForKey:@"pubId"] isEqual:[NSNull null]]) {
        [properties setValue:[NSString stringWithFormat:@"%@", [json objectForKey:@"pubID"]] forKey:@"pubID"];
    }
    
    if (![properties objectForKey:@"pubID"]) {
        // Use regex to pull out a pubID - YAY :D
        NSRegularExpression *regex = [NSRegularExpression regularExpressionWithPattern:@"pubId=(\\d+)"
                                                                               options:0
                                                                                 error:nil];
        NSString *string = [NSString stringWithFormat:@"%@", [json objectForKey:@"videoStillURL"]];
        NSTextCheckingResult *match = [regex firstMatchInString:string
                                                        options:0
                                                          range:NSMakeRange(0, [string length])];
        if (!match) {
            string = [NSString stringWithFormat:@"%@", [json objectForKey:@"thumbnailURL"]];
            match = [regex firstMatchInString:string
                                      options:0
                                        range:NSMakeRange(0, [string length])];
        }
        if (!match) {
            string = [NSString stringWithFormat:@"%@", [json objectForKey:@"FLVURL"]];
            match = [regex firstMatchInString:string
                                      options:0
                                        range:NSMakeRange(0, [string length])];
        }
        if (match) {
            [properties setValue:[string substringWithRange:[match rangeAtIndex:1]]
                          forKey:@"pubID"];
        }
    }
    
    BCRendition *rendition = nil;
    BCRenditionSet *renditionSet = nil;
    
    if (wvmRendition) {
        rendition = [[BCRendition alloc] initWithURL:[NSURL URLWithString:[wvmRendition objectForKey:@"url"]]];
    } else {
        // if no widevine rendition is found, attempt to playback the FLVURL as a normal video.
        rendition = [[BCRendition alloc] initWithURL:[NSURL URLWithString:[json objectForKey:@"FLVURL"]]];
    }
    renditionSet = [[BCRenditionSet alloc] initWithRenditions:[NSArray arrayWithObject:rendition]
                                                                deliveryMethod:[NSDictionary dictionary]];
    
    return [[BCVideo alloc] initWithRenditionSets: [NSArray arrayWithObject:renditionSet]
                                        properties: [NSDictionary dictionaryWithDictionary:properties]];
}
@end
