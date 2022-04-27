/*!
 @header Mind.h
 
 @brief This is the header file where the super-code is contained.
 
 The following  properties are allocated once during initializtion, in order to prevent frequent
 memory allocations for temporary variables during the update and backpropagation cycles.
 Some known properties are computed in advance in order to to avoid casting, integer division
 and modulus operations inside loops.
 
 There are also methods declared in this file. Refer to their documentations.
 
 @author Yongyang Nie
 @copyright  2017 Yongyang Nie
 @version    17.01.31
 */

#import <Foundation/Foundation.h>
#import <stdio.h>
#import <Accelerate/Accelerate.h>
#import <math.h>
#import "NeuralMath.h"

/*! @brief weights struct help us to create, modify all the weights which are float[] arrays. Accelerate framework doesn't allow NSMutableArray to other array types, therefore, weights is a nice wraper in memory */
typedef struct {
    
    /*! The current weights leading into all of the hidden nodes, serialized in a single array. float[] */
    float* hiddenWeights;
    /*! The weights leading into all of the hidden nodes from the previous round of training, serialized in a single array. Used for applying momentum during backpropagation. [Float] */
    float* previousHiddenWeights;
    /*! The current weights leading into all of the output nodes, serialized in a single array. [Float] */
    float* outputWeights;
    /*! The weights leading into all of the output nodes from the previous round of training, serialized in a single array. [Float]. Used for applying momentum during backpropagation. */
    float* previousOutputWeights;
    /*! Temporary storage while updating hidden weights, for use during backpropagation. [Float] */
    float* hiddenWeightsNew; ///new hidden weights
    /*! Temporary storage while updating output weights, for use during backpropagation.  [Float] */
    float* outputWeightsNew; ///new hidden weights
    
} Weights;

/*! @brief IOs, or inputs and outpus struct help us to create, modify all the i/o which are float[] arrays. Accelerate framework doesn't allow NSMutableArray to other array types, therefore, IOs is a nice wraper in memory*/
typedef struct {
    
    /*! The most recent set of inputs applied to the network.  [Float] */
    float* inputs;
    /*! The most recent output of all hidden nodes.  [Float] */
    float* hiddenOutputs;
    /*! The most recent output from the network. [Float] */
    float* outputs;
} IOs;

typedef struct {
    
    /*! @name hiddenErrorSums
     Temporary storage while calculating hidden errors, for use during backpropagation.  [Float] */
    float *hiddenErrorSums;
    /*! Temporary storage while calculating hidden errors, for use during backpropagation.  [Float] */
    float* hiddenErrors;
    /*! Temporary storage while calculating output errors, for use during backpropagation.  [Float] */
    float* outputErrors;
    
    
} Errors;

@interface Mind : NSObject

#pragma mark - Properties

/*! The number of input nodes to the network (read only). */
@property int numInputs;
/*! The number of hidden nodes in the network (read only). */
@property int numHidden;
/*! The number of output nodes from the network (read only). */
@property int numOutputs;

/*! The 'learning rate' parameter to apply during backpropagation. */
/*! This parameter may be safely tuned at any time, except for during a backpropagation cycle. */
@property (nonatomic) float learningRate;

/*! The 'momentum factor' to apply during backpropagation. This parameter may be safely tuned at any time, except for during a backpropagation cycle. */
@property float momentumFactor;

/*! (1 - momentumFactor) * learningRate. Used frequently during backpropagation. */
@property float mfLR;

/*! The number of input nodes, INCLUDING the bias node. */
@property int numInputNodes;
/*! The number of hidden nodes, INCLUDING the bias node. */
@property int numHiddenNodes;
/*! The total number of weights connecting all input nodes to all hidden nodes. */
@property int numHiddenWeights;
/*! The total number of weights connecting all hidden nodes to all output nodes. */
@property int numOutputWeights;

@property IOs *io;

@property Weights *weights;

@property Errors *errors;

@property float lmbda;

/*! The output error indices corresponding to each output weight.  = [Int]() */
@property (strong, nonatomic) NSMutableArray <NSNumber *>* outputErrorIndices;
/*! The hidden output indices corresponding to each output weight.  = [Int]() */
@property (strong, nonatomic) NSMutableArray <NSNumber *>* hiddenOutputIndices;
/*! The hidden error indices corresponding to each hidden weight.  = [Int]() */
@property (strong, nonatomic) NSMutableArray <NSNumber *>* hiddenErrorIndices;
/*! The input indices corresponding to each hidden weight.  = [Int]() */
@property (strong, nonatomic) NSMutableArray <NSNumber *>* inputIndices;

#pragma mark - Instance Methods

/*!
 @brief This is the constructor for the neural network.
 
 @param inputs number of inputs
 @param hidden number of hidden neurons
 @param outputs number of outpus
 @param learningRate the learning rate of the network, a good start is 0.7
 @param momentum the momentum of the learing, play around with this number, a good estimate is
 @param hws initialize the network with weights from other network or from the past. If initializing new network, set it as null
 
 @return instancetype
 
 @discussion This is a comprehensive constructor. Further improve this parameter so that it can reinitialize neural networks from the past. Also be able to add multiple hidden layers in the middle.
 */
- (instancetype)initWith:(int)inputs
                  hidden:(int)hidden
                 outputs:(int)outputs
            learningRate:(float)learningRate
                momentum:(float)momentum
                  lmbda:(float)lmbda
           hiddenWeights:(float *)hws
           outputWeights:(float *)opws;

/*!
 @brief Use the network to evaluate some output.
 @param inputs An array of `Float`s. Each element corresponding to one input node. Note: inputs.count has == to self.numInputNodes
 @return float* as an array of `Float`s
 @exception inputs has to equal to self.numInputs
 @discussion Propagates the given inputs through the neural network, returning the network's output. While the network is evaluating, it will add a bias node. The result will be cached.
 */
-(float *)forwardPropagation:(NSMutableArray <NSNumber *>*)inputs;

/*!
 Backward propagation method in this feed forward neural network. Trains the network by comparing its most recent output to the given 'answers', adjusting the network's weights as needed.
 @param answer The desired output for the most recent update to the network, as an array<nsnumber<float>>.
 @returns float calculated error
 @exception Answer and self.numOutputs has to be the same.
 */
-(float)backwardPropagation:(NSMutableArray <NSNumber *>*)answer;

/*!
 Train the network with data that you provides.
 @param inputs inputs to train the network
 @param answer the expected answer from the network. Used to backprop
 @param testInputs test inputs that will evaluate the errors
 @param testOutput expected output from the neural network, this will evaluate the errors
 @param threshold When the network's error eaches this point, training will stop.
 @exception inputs, answer, testInputs and testOutputs all have to correspond to the amount of neurons in the network. The error margin can not be > 0
 */
-(void)train:(NSArray <NSArray <NSNumber*>*>*)inputs
      answer:(NSArray <NSArray <NSNumber *>*>*)answer
  testInputs:(NSArray <NSArray <NSNumber*>*>*)testInputs
 testOutputs:(NSArray <NSArray <NSNumber *>*>*)testOutput
   threshold:(float)threshold;


/*!
 Set random weights for all weights. The random weights are between {1, -1}
 */
-(void)randomWeightAllLayers;

-(void)print:(float *)array count:(int)count;

-(void)ResetLearningRate:(float)learningRate;

-(void)ResetMomentum:(float)momentum;

@end
