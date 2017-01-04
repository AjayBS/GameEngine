#include "GameManager.h"
#include "PlayerController.h"
#include "MonsterController.h"
#include "Point2.h"
#include "HeapManager.h"
#include "Macros.h"


using namespace HeapManagerProxy;
//In branch 1.04.01



void TestConstFunctions();
void TestIsNANFunctionAndFloatFunction();
void TestCaseForCopyAndMoveConstructor();

void main() {
	const size_t sizeHeap = INITIAL_HEAP_SIZE;
	const myint_t numDescriptors = INITIAL_DESCRIPTOR_SIZE;
	void * pHeapMemory = _aligned_malloc(sizeHeap, DEFAULT_ALIGNMENT);
	HeapManager * pHeapManager;
	pHeapManager = CreateHeapManager(pHeapMemory, sizeHeap, numDescriptors);
	SetHeapManager(pHeapManager);

	myint_t count = pHeapManager->ShowFreeBlocks();

	GameManager *manager = new GameManager();

	manager->InitializeGameObjects(pHeapManager);
	manager->UpdateGameObject();
	
	TestConstFunctions();
	TestIsNANFunctionAndFloatFunction();
	TestCaseForCopyAndMoveConstructor();

	_aligned_free(pHeapMemory);
}


void TestConstFunctions() {
	 const Point2 A(0.0f,0.0f);
	const Point2 B(1.0f, 1.0f);
	
	// These should work
	Point2 C = A + B;
	C.SetPositionX(A.GetPositionX());
	C = A + B;
	
	// These shouldn't work
	// A.SetPositionX(1.0f);
	// A = C + B;
	// A += C; 
}

void TestIsNANFunctionAndFloatFunction() {
	// Returns false
	float number = 2.0f;
	bool check = IsNAN(number);

	// Returns true
	float number2 = sqrt(-1.0f);
	check = IsNAN(number2);

	number2 = 2.0f;
	// Returns true
	bool checkEqual = AreAboutEqual(number, number2);
	number2 = 3.0f;
	// Returns false
	checkEqual = AreAboutEqual(number, number2);
	
}

void TestCaseForCopyAndMoveConstructor(){
	  GameObject m1("m1", Point2(0,0));

	//  // copy constructor

	  GameObject m2 = m1;

	//  //// copy assignment

	  GameObject m3("m3", Point2(0,0));

	  m3 = m1;

	//  //// move constructor

	  GameObject m4 = std::move(m2);

	//  //// move assignment

	  GameObject m5("m5", Point2(0,0));

	//  m5 = std::move(m4);
}

