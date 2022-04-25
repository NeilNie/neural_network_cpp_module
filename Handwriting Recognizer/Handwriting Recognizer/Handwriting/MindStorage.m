//
//  MindStorage.m
//  Handwriting
//
//  Created by Yongyang Nie on 2/6/17.
//  Copyright © 2017 Yongyang Nie. All rights reserved.
//

#import "MindStorage.h"
#import <Foundation/Foundation.h>

@implementation MindStorage

+(BOOL)storeMind:(Mind *)mind path:(NSString *)path{
    
    NSMutableArray *hiddenWeights = [MindStorage convertToArray:mind.weights->hiddenWeights count:mind.numHiddenWeights];
    NSMutableArray *outputWeights = [MindStorage convertToArray:mind.weights->outputWeights count:mind.numOutputWeights];
    NSDictionary *dic = @{@"hiddenWeights": hiddenWeights,
                          @"outputWeights": outputWeights,
                          @"inputCount": [NSNumber numberWithInt:mind.numInputs],
                          @"hiddenCount" : [NSNumber numberWithInt:mind.numHidden],
                          @"outputCount": [NSNumber numberWithInt:mind.numOutputs],
                          @"rate": [NSNumber numberWithFloat:mind.learningRate],
                          @"momentum": [NSNumber numberWithInt:mind.momentumFactor],
                          @"lmbda": [NSNumber numberWithInt:mind.lmbda]};
    
    NSData *data = [NSKeyedArchiver archivedDataWithRootObject:dic];
    NSError *error;
    [data writeToFile:path options:NSDataWritingAtomic error:&error];
    NSLog(@"%@", error);
    if (error)
        return NO;
    return YES;
}

+(Mind *)getMind:(NSString *)path{
    
    NSData *data = [NSData dataWithContentsOfFile:path];
    NSDictionary *dic = [NSKeyedUnarchiver unarchiveObjectWithData:data];
    
    NSMutableArray *hiddenWeights = [dic objectForKey:@"hiddenWeights"];
    NSMutableArray *outputWeight = [dic objectForKey:@"outputWeights"];
    
    float *hws = [MindStorage convertToFloats:hiddenWeights count:hiddenWeights.count];
    float *opws = [MindStorage convertToFloats:outputWeight count:outputWeight.count];
    
    Mind *mind = [[Mind alloc] initWith:[[dic objectForKey:@"inputCount"] intValue]
                                 hidden:[[dic objectForKey:@"hiddenCount"] intValue]
                                outputs:[[dic objectForKey:@"outputCount"] intValue]
                           learningRate:[[dic objectForKey:@"rate"] floatValue]
                               momentum:[[dic objectForKey:@"momentum"] floatValue]
                                 lmbda:[[dic objectForKey:@"lmbda"] floatValue]
                          hiddenWeights:hws
                          outputWeights:opws];
    return mind;
}

+(NSMutableArray *)convertToArray:(float *)array count:(int)count{
    
    NSMutableArray *objects = [NSMutableArray array];
    for (int i = 0; i < count; i++) {
        [objects addObject:[NSNumber numberWithFloat:array[i]]];
    }
    return objects;
}

+(float *)convertToFloats:(NSMutableArray *)array count:(NSUInteger)count{
    
    float *f = calloc(count, sizeof(float));
    for (int i = 0; i < array.count; i++) {
        f[i] = [array[i] floatValue];
    }
    return f;
}

@end
