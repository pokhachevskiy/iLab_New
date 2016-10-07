/*
#include "STL_CVector.h"
using std::cout;
using std::endl;
int main()
{
    STL_CVector<int> arr(5);
    for (int i = 0; i < 5; i++)
        arr.push_back(i*6 + 9);
    arr.pop_back();
    STL_CVector<int> my_arr(arr);
    STL_CVector<int> vec;
    vec = arr;
    arr[3] = 100;
    arr.insert(arr.begin() + 5, 5, 6);
     cout << endl << "this is arr (((vec=arr after arr is changed"<< endl;
    for (auto it = arr.begin(); it != arr.end(); ++it)
        std::cout << *it << std::endl;
    cout << endl << endl;
    STL_CVector<int> vectorr;
    vectorr.assign(10, 67);
    for (auto it = vectorr.begin(); it != vectorr.end(); ++it)
        std::cout << *it << std::endl;
    if ((arr > vec))
        std::cout<<"arr > vec \n";
    for (auto it = my_arr.begin(); it != my_arr.end(); ++it)
        std::cout << *it << std::endl;
    std::cout<<std::endl;
    arr.Vector_Dump();
    arr[2] = -1;
    std::cout<<arr.is_empty() << std::endl;
    for (auto it = arr.begin(); it != arr.end(); ++it)
        std::cout << *it << std::endl;
    my_arr.clear();
    for (int i = 0; i < 8; i++)
        my_arr.push_back(i*81 + 25);
    std::cout<<std::endl;
    std::cout<<std::endl;
    for (auto it = my_arr.begin(); it != my_arr.end(); ++it)
        std::cout << *it << std::endl;
    for (auto it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << std::endl;
    return 0;
}
*/
