# Totem
A graph processing engine for hybrid CPU and GPU platforms

Do the following to run on PSC Bridges:
(Your personal run will need to modify the make.defs file to point GTEST to your folder locations)
GTEST=/..../Totem/src/thirdparty/googletest/googletest
DATAFOLDER=/..../Totem/data

The following is the totem graph file format template:
 
       #Nodes: vertex_count
       #Edges: edge_count
       #Directed|Undirected
       [VERTEX LIST] [EDGE LIST]      
 
The format for the converter is slightly different than what is mentioned in the totem_graph.h file.
The *.totem files have the vertex's listed from small to large.

graph data needs to be converted to the *.totem format.

       COMPILE:    g++ -Wall -g -std=c++11 convert_el2totem.cpp -o convert
       USE: ./convert <edge list file> <totem file> -d | -u (for directed or undirected)



TO MAKE TOTEM:
1) clone the repository to your directory
2) go to the Totem/src/thirdparty and unpack the google test zip into the thirdparty folder.
3) load the gcc/5.3 and cuda/8.0 modules.
4) run "make" from Totem/src/ (many WARNINGS present).
5) interact --gpu(check if modules are loaded. be sure to add in same order as step 3!)
6) to run move to the build/bin folder: ./benchmark -h for help

#######################################################################################
#######################  FIXED ERRORS FROM ORIG FILE ##################################
TOTEM WORK TO FIX...

1) PROBLEM:

[gsiegfri@br018 src]$ make
make[1]: Entering directory `/pylon5/cc3uv3p/gsiegfri/projectGPA/totem/src/benchmark'
/usr/local/cuda/bin/nvcc  -Xptxas -dlcm=cg -dc -DFEATURE_SM35 -g -Xcompiler "-fopenmp -fno-strict-aliasing" -O3 -I. -I/usr/local/cuda/include -gencode=arch=compute_35,code=\"sm_35,compute_35\" -D__STDC_LIMIT_MACROS  -I../totem -I../alg -c totem_benchmark_cmdline.cu -o ../build/EID32_CC35/obj/benchmark/totem_benchmark_cmdline.cu.o
/bin/sh: /usr/local/cuda/bin/nvcc: No such file or directory
make[1]: *** [../build/EID32_CC35/obj/benchmark/totem_benchmark_cmdline.cu.o] Error 127
make[1]: Leaving directory `/pylon5/cc3uv3p/gsiegfri/projectGPA/totem/src/benchmark'
make: *** [benchmark] Error 2

1) FIX:

Changed the make.defs in the cuda build location.

2) PROBLEM:

[gsiegfri@br005 src]$ make
make[1]: Entering directory `/pylon5/cc3uv3p/gsiegfri/projectGPA/totem/src/benchmark'
/opt/packages/cuda/8.0//bin/nvcc  -Xptxas -dlcm=cg -dc -DFEATURE_SM35 -g -Xcompiler "-fopenmp -fno-strict-aliasing" -O3 -I. -I/opt/packages/cuda/8.0//include -gencode=arch=compute_35,code=\"sm_35,compute_35\" -D__STDC_LIMIT_MACROS  -I../totem -I../alg -c totem_benchmark_cmdline.cu -o ../build/EID32_CC35/obj/benchmark/totem_benchmark_cmdline.cu.o
../totem/totem_comkernel.cuh(163): error: function "atomicAdd(double *, double)" has already been defined

1 error detected in the compilation of "/tmp/tmpxft_00004db0_00000000-5_totem_benchmark_cmdline.cpp4.ii".
make[1]: *** [../build/EID32_CC35/obj/benchmark/totem_benchmark_cmdline.cu.o] Error 2
make[1]: Leaving directory `/pylon5/cc3uv3p/gsiegfri/projectGPA/totem/src/benchmark'
make: *** [benchmark] Error 2

2) FIX: 

Comment out the entire function attributed to atomic_add.

3) PROBLEM:

TDC_LIMIT_MACROS  -I../totem -c totem_page_rank_hybrid.cu -o ../build/EID32_CC35/obj/alg/totem_page_rank_hybrid.cu.o
/opt/packages/cuda/8.0/bin/nvcc  -Xptxas -dlcm=cg -dc -DFEATURE_SM35 -g -Xcompiler "-fopenmp -fno-strict-aliasing" -O3 -I. -I/opt/packages/cuda/8.0/include -gencode=arch=compute_35,code=\"sm_35,compute_35\" -D__STDC_LIMIT_MACROS  -I../totem -c totem_stress.cu -o ../build/EID32_CC35/obj/alg/totem_stress.cu.o
totem_stress.cu: In function ‘error_t stress_unweighted_cpu(const graph_t*, weight_t**)’:
totem_stress.cu:391:1: error: for statement expected before ‘}’ token
       for (vid_t v = 0; v < graph->vertex_count; v++) {
 ^
make[2]: *** [../build/EID32_CC35/obj/alg/totem_stress.cu.o] Error 1
make[2]: Leaving directory `/pylon5/cc3uv3p/gsiegfri/projectGPA/totem/src/alg'
make[1]: *** [libalg] Error 2
make[1]: Leaving directory `/pylon5/cc3uv3p/gsiegfri/projectGPA/totem/src/benchmark'
make: *** [benchmark] Error 2

3) FIX:

Removed line 390 with the OMP(omp parallel for).

4) PROBLEM: 

make[1]: Leaving directory `/pylon5/cc3uv3p/gsiegfri/projectGPA/totem/src/thirdparty/graph500-2.1.4-energy/totem'
make[1]: Entering directory `/pylon5/cc3uv3p/gsiegfri/projectGPA/totem/src/test'
makefile:15: *** GTEST environment variable is not defined.  Stop.
make[1]: Leaving directory `/pylon5/cc3uv3p/gsiegfri/projectGPA/totem/src/test'
make: *** [test] Error 2

4) FIX:

CHange some lines at the top of the make.def file. Used a zip file. to add GTEST and datafolder

5) PROBLEM: 

make[1]: Entering directory `/totem/src/test'
"/opt/packages/cuda/8.0/bin/nvcc"  -Xptxas -dlcm=cg -dc -DFEATURE_SM35 -g -Xcompiler "-fopenmp -fno-strict-aliasing" -O3 -I. -I"/opt/packages/cuda/8.0/bin/.."/include -gencode=arch=compute_35,code=\"sm_35,compute_35\" -D__STDC_LIMIT_MACROS -I. -I/totem/src/thirdparty/googletest/googletest/include/ -I/totem/src/thirdparty/googletest/googletest -I../totem -I../alg -c totem_hash_table_unittest.cu -o ../build/EID32_CC35/obj/tests/totem_hash_table_unittest.cu.o
/totem/src/thirdparty/googletest/googletest/include/gtest/internal/gtest-linked_ptr.h(114): warning: controlling expression is constant

/totem/src/thirdparty/googletest/googletest/include/gtest/internal/gtest-linked_ptr.h(132): warning: controlling expression is constant

totem_hash_table_unittest.cu(133): error: not a class or struct name

totem_hash_table_unittest.cu(133): error: identifier "DummyTest" is undefined

totem_hash_table_unittest.cu(133): error: no instance of function template "testing::internal::ParameterizedTestCaseRegistry::GetTestCasePatternHolder" matches the argument list
            argument types are: (const char [10], testing::internal::CodeLocation)
            object type is: testing::internal::ParameterizedTestCaseRegistry

/totem/src/thirdparty/googletest/googletest/include/gtest/internal/gtest-param-util.h(441): error: class "DummyTest_ValueParameterizedTestsAreNotSupportedOnThisPlatform_Test" has no member "ParamType"
          detected during instantiation of class "testing::internal::TestMetaFactory<TestCase> [with TestCase=DummyTest_ValueParameterizedTestsAreNotSupportedOnThisPlatform_Test]" 
totem_hash_table_unittest.cu(133): here

/totem/src/thirdparty/googletest/googletest/include/gtest/internal/gtest-param-util.h(443): error: class "DummyTest_ValueParameterizedTestsAreNotSupportedOnThisPlatform_Test" has no member "ParamType"
          detected during instantiation of class "testing::internal::TestMetaFactory<TestCase> [with TestCase=DummyTest_ValueParameterizedTestsAreNotSupportedOnThisPlatform_Test]" 
totem_hash_table_unittest.cu(133): here

/totem/src/thirdparty/googletest/googletest/include/gtest/internal/gtest-param-util.h(405): error: class "DummyTest_ValueParameterizedTestsAreNotSupportedOnThisPlatform_Test" has no member "ParamType"
          detected during:
            instantiation of class "testing::internal::ParameterizedTestFactory<TestClass> [with TestClass=DummyTest_ValueParameterizedTestsAreNotSupportedOnThisPlatform_Test]" 
(448): here
            instantiation of "testing::internal::TestFactoryBase *testing::internal::TestMetaFactory<TestCase>::CreateTestFactory(testing::internal::TestMetaFactory<TestCase>::ParamType) [with TestCase=DummyTest_ValueParameterizedTestsAreNotSupportedOnThisPlatform_Test]" 
(445): here
            implicit generation of "testing::internal::TestMetaFactory<TestCase>::~TestMetaFactory() [with TestCase=DummyTest_ValueParameterizedTestsAreNotSupportedOnThisPlatform_Test]" 
(445): here
            instantiation of class "testing::internal::TestMetaFactory<TestCase> [with TestCase=DummyTest_ValueParameterizedTestsAreNotSupportedOnThisPlatform_Test]" 
(445): here
            instantiation of "testing::internal::TestMetaFactory<TestCase>::TestMetaFactory() [with TestCase=DummyTest_ValueParameterizedTestsAreNotSupportedOnThisPlatform_Test]" 
totem_hash_table_unittest.cu(133): here

6 errors detected in the compilation of "/tmp/tmpxft_000054a9_00000000-7_totem_hash_table_unittest.cpp1.ii".
make[1]: *** [../build/EID32_CC35/obj/tests/totem_hash_table_unittest.cu.o] Error 2
make[1]: Leaving directory `/totem/src/test'
make: *** [test] Error 2

5) FIX:

Modified all the test files with the googletest source file #8.
Commenting out all test files with TEST_P at the very end.



