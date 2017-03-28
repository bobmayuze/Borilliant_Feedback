#include <iostream>
#include <cmath>
#include <string>
using namespace std;

#include "vec.h"

int main() {
    
    // ---------------------------------------------------
    // initialize v1 with 10 values...  the multiples of 5
    Vec<int> v1( 10, 0 );
    Vec<int>::size_type i;
    for ( i = 0; i < v1.size(); i++) {
        v1[i] = 5 * i;
    }
    cout << "v1.size() = " << v1.size() << ".  Should be 10.\n";
    cout << "Contents of v1 (multiples of 5):";
    for ( i = 0; i<v1.size(); ++i ) {
        cout << " " << v1[i];
    }
    cout << endl;
    
    // --------------------------------------------------------------------------
    // make v2 be a copy of v1, but then overwrite the 2nd half with the 1st half
    Vec<int> v2( v1 );
    v2[ 9 ] = v2[ 0 ];
    v2[ 8 ] = v2[ 1 ];
    v2[ 7 ] = v2[ 2 ];
    v2[ 6 ] = v2[ 3 ];
    v2[ 5 ] = v2[ 4 ];
    cout << "Contents of v1 (still multiples of 5):";
    for ( i = 0; i<v1.size(); ++i )
        cout << " " << v1[i];
    cout << endl;
    cout << "Contents of v2 (now palindrome):";
    for ( i = 0; i<v2.size(); ++i )
        cout << " " << v2[i];
    cout << endl;
    
    // ------------------------------------------
    // make v3 be a copy of v2, but then clear it
    Vec<int> v3;
    v3 = v2;
    v3.clear();
    cout << "\nAfter copying v2 to v3 and clearing v3,  v2.size() = "
    << v2.size() << " and v3.size() = " << v3.size() << endl;
    cout << "Contents of v2 (should be unchanged):";
    for ( i = 0; i<v2.size(); ++i ) {
        cout << " " << v2[i];
    }
    cout << endl;
    
    // --------------
    // test push back
    cout << "\nNow testing push_back.  Adding 3, 6, 9 to v2:\n";
    v2.push_back( 3 );
    v2.push_back( 6 );
    v2.push_back( 9 );
    cout << "v2 is now: \n";
    for ( i = 0; i<v2.size(); ++i ) {
        cout << " " << v2[i];
    }
    cout << endl;
    
    // -----------
    // test resize
    v1.resize(20,100);
    cout << "\nNow testing resize.  Resizing v1 to have 20 elements and v2 to have 2 elements\n";
    cout << "v1 is now (should have 100s at the end): \n";
    for ( i = 0; i<v1.size(); ++i )
        cout << " " << v1[i];
    cout << endl;
    v2.resize(2,100);
    cout << "v2 is now: \n";
    for ( i = 0; i<v2.size(); ++i )
        cout << " " << v2[i];
    cout << endl;
    
    // ------------------------
    // test of a vec of doubles
    cout << "\nStarting from an empty vector, z,  of doubles and doing\n"
    << "5 push_backs\n";
    Vec<double> z;
    for ( i = 0; i<5; ++i )
        z.push_back( sqrt( double(10*(i+1)) ));
    cout << "Contents of vector z: ";
    for ( Vec<double>::size_type j = 0; j < z.size(); j++ )
        cout << " " << z[j];
    cout << endl;
    
    
    
    // ADD MORE TEST CASES HERE
    //    Vec<int> v;
    //    v.push_back(11);
    //    v.push_back(22);
    //    v.push_back(33);
    //    v.push_back(11);
    //    v.push_back(55);
    //    v.push_back(22);
    //    unsigned int count = remove_matching_elements(v, 11);
    //    cout << "Remove " << count << " elements" << endl;
    //
    //    cout << "After: ";
    //    for (unsigned int i =0; i<v.size(); ++i)
    //        cout << v[i] <<' ';
    //    cout << endl;
    
    Vec<int> vv;
    for (unsigned int i = 0; i < 20; ++i) {
        vv.push_back(pow(i,2));
    }
    vv.print();
    unsigned int count;
    for (unsigned int i = 5; i < 15; ++i) {
        count = remove_matching_elements(vv, int(pow(i,2)));
        cout << "Remove " << count << " elements" << endl;
        
        cout << "After: ";
        for (unsigned int i =0; i<vv.size(); ++i)
            cout << vv[i] <<' ';
        cout << endl;
        vv.shrink();
        vv.print();
    }
    
    Vec<int> vvv;
    vvv.push_back(1);
    vvv.print();
    count = remove_matching_elements(vvv, 1);
    cout << "Remove " << count << " elements" << endl;
    cout << "After: ";
    for (unsigned int i =0; i<vvv.size(); ++i)
        cout << vvv[i] <<' ';
    cout << endl;
    vvv.shrink();
    vvv.print();
    
    
    Vec<int> vvvv;
    vvvv.push_back(1);
    vvvv.push_back(1);
    vvvv.print();
    count = remove_matching_elements(vvvv, 2);
    cout << "Remove " << count << " elements" << endl;
    cout << "After: ";
    for (unsigned int i =0; i < vvvv.size(); ++i)
        cout << vvvv[i] <<' ';
    cout << endl;
    vvvv.shrink();
    vvvv.print();
    
    Vec<double> vvvvv;
    vvvvv.push_back(1.1);
    vvvvv.push_back(2.2);
    vvvvv.push_back(3.3);
    vvvvv.push_back(4.4);
    vvvvv.print();
    count = remove_matching_elements(vvvvv, 4.4);
    count = remove_matching_elements(vvvvv, 3.3);

    cout << "Remove " << count << " elements" << endl;
    cout << "After: ";
    for (unsigned int i =0; i < vvvvv.size(); ++i)
        cout << vvvvv[i] <<' ';
    cout << endl;
    vvvvv.shrink();
    vvvvv.print();
    
//    Vec<char> vvvvvv;
//    vvvvvv.push_back('A');
//    vvvvvv.push_back('S');
//    vvvvvv.push_back('G');
//    vvvvvv.push_back('F');
//    vvvvvv.print();
//    count = remove_matching_elements(vvvvvv, 'S');
//    count = remove_matching_elements(vvvvvv, 'G');
//    
//    cout << "Remove " << count << " elements" << endl;
//    cout << "After: ";
//    for (unsigned int i =0; i < vvvvvv.size(); ++i)
//        cout << vvvvvv[i] <<' ';
//    cout << endl;
//    vvvvvv.shrink();
//    vvvvvv.print();
    
    return 0;
}
