#include "GestureSVM.h"
#include <stdio.h>
#include <stdlib.h>

#define NULL 0

void convertToSVMVec(const std::vector<float>& vec, svm_node* destination)
{
		svm_node node;
        for(unsigned int i = 0;i < vec.size();i++)
		{
			node.index = i+1;
			node.value = (double) vec.at(i);
			destination[i] = node;
		}
		node.index =-1;
		destination[vec.size()] = node;		
}
void GestureSVM::train(const std::vector<float>& feature,int classId)
{
	svm_node* vec = new svm_node[feature.size()+1];
	convertToSVMVec(feature,vec);
	mFeatureSet.push_back(vec);
	mClassIdx.push_back(classId);
}
int GestureSVM::predictGesture(const std::vector<float>& feature)
{
    if(!mIsModel)
        printf("Error GestureSVM:can't predict without a model..run generateModel() before or use loadModel()\n");
	svm_node* preVec = new svm_node[feature.size()+1]; 
	convertToSVMVec(feature,preVec);
	int result = (int) svm_predict(mModel,preVec);
	delete[] preVec;
    return result;
}

void GestureSVM::saveModel(std::string filePath)
{
    svm_save_model(filePath.data(),mModel);
}

void GestureSVM::loadModel(std::string filePath)
{
    if(mModel)
    {
        //    svm_free_and_destroy_model(&mModel);
    }
    mModel = svm_load_model(filePath.data());
    mIsModel = true;
}
void GestureSVM::generateModel()
{
    //set libsm problem structure
	mProblem.l = mFeatureSet.size();		//number of trainings data (2 training vectors here
	mProblem.y = mClassIdx.data();		

    //fill svm structure with trainings data
	mProblem.x = mFeatureSet.data();

    //set proble depending params
    mParam.gamma = (mProblem.l > 0)?(1.0 / mProblem.l):0;	// 1/num_features if l >0

	const char* error_msg = svm_check_parameter(&mProblem,&mParam);
	if(error_msg)
	{
        printf("ERROR svm params: %s\n",error_msg);
		exit(1);
	}
	
	mModel = svm_train(&mProblem,&mParam);
    mIsModel = true;

}
GestureSVM::GestureSVM(void)
{
    mIsModel = false;
    mModel = NULL;

    //set default param values
    mParam.svm_type = C_SVC;
    mParam.kernel_type = RBF;
    mParam.degree = 3;
    mParam.gamma = 0;	// 1/num_features if l >0
    mParam.coef0 = 0;
    mParam.nu = 0.5;
    mParam.cache_size = 100;
    mParam.C = 1;
    mParam.eps = 1e-3;
    mParam.p = 0.1;
    mParam.shrinking = 1;
    mParam.probability = 0;
    mParam.nr_weight = 0;
    mParam.weight_label = NULL;
    mParam.weight = NULL;
}


GestureSVM::~GestureSVM(void)
{
    svm_destroy_param(&mParam);
    svm_free_and_destroy_model(&mModel);

    //delete problem data
	std::vector<svm_node*>::iterator iter;
	for(iter = mFeatureSet.begin(); iter != mFeatureSet.end();iter++)
	{
		delete[] *iter;
	}
}
