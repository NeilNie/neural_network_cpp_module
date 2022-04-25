//
//  NeuralMath.h
//  Simple Neural Network
//
//  Created by Yongyang Nie on 1/25/17.
//  Copyright © 2017 Yongyang Nie. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NeuralMath : NSObject

+(float)sigmoid:(float)x;

+(float)sigmoidPrime:(float)y;

+(NSMutableArray *__nonnull)fillMat:(int)h w:(int)w;

+(NSMutableArray <NSMutableArray *>* __nonnull)multiply:(NSMutableArray <NSMutableArray *>* __nonnull)mat1 toMat:(NSMutableArray <NSMutableArray *>* __nonnull)mat2;

@end
