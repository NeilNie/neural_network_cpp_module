//
//  MindStorage.h
//  Handwriting
//
//  Created by Yongyang Nie on 2/6/17.
//  Copyright © 2017 Yongyang Nie. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Mind.h"

@interface MindStorage : NSObject

+(BOOL)storeMind:(Mind *)mind path:(NSString *)path;

+(Mind *)getMind:(NSString *)path;

@end
