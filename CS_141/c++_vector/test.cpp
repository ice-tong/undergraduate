#include "vector.cpp"
using namespace std;

int main() {
    Vector<int> intVec{1,3,5,7,9};
    Vector<int> intVec2{3,1};
    Vector<double> doubleVec{1.5,2.5,3.5,4.5};
    Vector<int> iv(intVec);
    Vector<double> dv(doubleVec);
    cout << "intVec" << intVec << endl;
    cout << "intVec2" << intVec2 << endl;
    cout << "iv" << iv << endl;
    cout << "doubleVec" << doubleVec << endl;
    cout << "dv" << dv << endl << endl;;

    cout << "intVec[2] = " << intVec[2] << endl;
    cout << "dv[0] = " << dv[0] << endl;
    try {
	intVec[5];
    }
    catch(const char * e) {
	cout << "intVec[5]: " << e << endl << endl;
    }

    cout << "intVec * iv = " << intVec * iv << endl;
    cout << "doubleVec * dv = " << doubleVec * dv << endl << endl;

    cout << "iv + intVec2 = " << iv + intVec2 << endl;
    cout << "intVec2 + iv = " << intVec2 + iv << endl << endl;

    cout << "(dv = dv + dv): " << (dv = dv + dv) << endl;
    cout << "(intVec2 = intVec): " << (intVec2 = intVec) << endl << endl;

    cout << "(intVec == iv) = " << (intVec == iv) << endl;
    cout << "(intVec == intVec2) = " << (intVec == intVec2) << endl;
    cout << "(intVec != intVec2) = " << (intVec != intVec2) << endl << endl;
    
    cout << "doubleVec * 10 = " << 10 * doubleVec << endl;
    cout << "iv + 50 = " << 50 + iv << endl << endl;
    return 0;
}
