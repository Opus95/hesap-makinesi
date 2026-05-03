#include <iostream>
#include <cmath>
#include <complex>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <bitset>

using namespace std;

const double PI    = acos(-1.0);
const double E_NUM = exp(1.0);
const double PHI   = (1.0 + sqrt(5.0)) / 2.0;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

double getDouble(const string& prompt) {
    double val;
    while (true) {
        cout << prompt;
        if (cin >> val) return val;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  [!] Gecersiz giris. Lutfen bir sayi girin.\n";
    }
}

int getInt(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) return val;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  [!] Gecersiz giris. Lutfen tam sayi girin.\n";
    }
}

void showResult(const string& label, double result, int precision = 10) {
    cout << "\n  ┌─────────────────────────────────────┐\n";
    cout << "  │  " << left << setw(14) << label
         << " = " << right << setprecision(precision) << result << "\n";
    cout << "  └─────────────────────────────────────┘\n";
}

void showResultStr(const string& label, const string& result) {
    cout << "\n  ┌─────────────────────────────────────┐\n";
    cout << "  │  " << left << setw(14) << label << " = " << result << "\n";
    cout << "  └─────────────────────────────────────┘\n";
}

void printHeader(const string& title) {
    clearScreen();
    cout << "\n";
    cout << "  ╔══════════════════════════════════════════╗\n";
    cout << "  ║       HESAP MAKINESI — C++       ║\n";
    cout << "  ╠══════════════════════════════════════════╣\n";
    cout << "  ║  " << left << setw(42) << title << "║\n";
    cout << "  ╚══════════════════════════════════════════╝\n\n";
}

void moduleBasic() {
    printHeader("TEMEL ISLEMLER");
    cout << "  [1] Toplama       [2] Cikarma\n";
    cout << "  [3] Carpma        [4] Bolme\n";
    cout << "  [5] Kuvvet (x^y)  [6] Kalan (mod)\n";
    cout << "  [7] Tam Kisim (floor/ceil/round)\n";
    cout << "  [0] Ana Menu\n\n";

    int ch = getInt("  Seciminiz: ");
    if (ch == 0) return;

    if (ch >= 1 && ch <= 6) {
        double a = getDouble("  Birinci sayi: ");
        double b = getDouble("  Ikinci sayi : ");
        switch (ch) {
            case 1: showResult("Toplam", a + b); break;
            case 2: showResult("Fark", a - b); break;
            case 3: showResult("Carpim", a * b); break;
            case 4:
                if (b == 0) { cout << "  [!] Sifira bolme hatasi!\n"; }
                else         { showResult("Bolum", a / b); }
                break;
            case 5: showResult("Kuvvet", pow(a, b)); break;
            case 6:
                if ((long long)b == 0) { cout << "  [!] Sifira mod hatasi!\n"; }
                else { showResult("Kalan", fmod(a, b)); }
                break;
        }
    } else if (ch == 7) {
        double a = getDouble("  Sayi: ");
        cout << "\n  floor(" << a << ") = " << floor(a) << "\n";
        cout << "  ceil ("  << a << ") = " << ceil(a)  << "\n";
        cout << "  round("  << a << ") = " << round(a) << "\n";
    }
}

void moduleTrig() {
    printHeader("TRIGONOMETRI");
    cout << "  Acilari hangi birimde girmek istersiniz?\n";
    cout << "  [1] Derece   [2] Radyan\n\n";
    int unit = getInt("  Seciminiz: ");

    cout << "\n  [1] sin   [2] cos   [3] tan\n";
    cout << "  [4] asin  [5] acos  [6] atan\n";
    cout << "  [7] sinh  [8] cosh  [9] tanh\n";
    cout << "  [10] atan2(y,x)\n\n";
    int ch = getInt("  Fonksiyon: ");

    double deg2rad = (unit == 1) ? PI / 180.0 : 1.0;

    if (ch >= 1 && ch <= 9) {
        double a = getDouble("  Deger: ");
        double rad = a * deg2rad;
        switch (ch) {
            case 1: showResult("sin", sin(rad)); break;
            case 2: showResult("cos", cos(rad)); break;
            case 3:
                if (fabs(cos(rad)) < 1e-12) cout << "  [!] Tanjant tanimsiz!\n";
                else showResult("tan", tan(rad));
                break;
            case 4:
                if (a < -1 || a > 1) cout << "  [!] asin tanim kumesi [-1,1]\n";
                else showResult("asin(rad)", asin(a));
                break;
            case 5:
                if (a < -1 || a > 1) cout << "  [!] acos tanim kumesi [-1,1]\n";
                else showResult("acos(rad)", acos(a));
                break;
            case 6: showResult("atan(rad)", atan(a)); break;
            case 7: showResult("sinh", sinh(rad)); break;
            case 8: showResult("cosh", cosh(rad)); break;
            case 9: showResult("tanh", tanh(rad)); break;
        }
    } else if (ch == 10) {
        double y = getDouble("  y degeri: ");
        double x = getDouble("  x degeri: ");
        showResult("atan2(rad)", atan2(y, x));
    }
}

void moduleLogPow() {
    printHeader("LOGARITMA & KUVVET");
    cout << "  [1] ln(x)       [2] log10(x)\n";
    cout << "  [3] log_b(x)    [4] e^x\n";
    cout << "  [5] 10^x        [6] sqrt(x)\n";
    cout << "  [7] cbrt(x)     [8] x! (faktoriyel)\n";
    cout << "  [9] n. kok\n\n";

    int ch = getInt("  Seciminiz: ");
    double x, b;

    switch (ch) {
        case 1:
            x = getDouble("  x: ");
            if (x <= 0) cout << "  [!] ln tanimsiz (x > 0 olmali)\n";
            else showResult("ln(x)", log(x));
            break;
        case 2:
            x = getDouble("  x: ");
            if (x <= 0) cout << "  [!] log10 tanimsiz (x > 0 olmali)\n";
            else showResult("log10(x)", log10(x));
            break;
        case 3:
            b = getDouble("  Taban b: ");
            x = getDouble("  x: ");
            if (b <= 0 || b == 1 || x <= 0)
                cout << "  [!] Gecersiz degerler (b>0, b!=1, x>0)\n";
            else showResult("log_b(x)", log(x) / log(b));
            break;
        case 4:
            x = getDouble("  x: ");
            showResult("e^x", exp(x));
            break;
        case 5:
            x = getDouble("  x: ");
            showResult("10^x", pow(10.0, x));
            break;
        case 6:
            x = getDouble("  x: ");
            if (x < 0) cout << "  [!] Negatif sayinin karekoku tanimsiz (Reel)\n";
            else showResult("sqrt(x)", sqrt(x));
            break;
        case 7:
            x = getDouble("  x: ");
            showResult("cbrt(x)", cbrt(x));
            break;
        case 8: {
            int n = getInt("  n (n <= 20 onerilir): ");
            if (n < 0) { cout << "  [!] Negatif faktoriyel tanimsiz\n"; break; }
            long long fact = 1;
            for (int i = 2; i <= n; i++) fact *= i;
            cout << "\n  " << n << "! = " << fact << "\n";
            break;
        }
        case 9: {
            double n_root = getDouble("  Kok derecesi (n): ");
            x = getDouble("  x: ");
            if (n_root == 0) { cout << "  [!] Kok derecesi 0 olamaz\n"; break; }
            showResult("n. kok", pow(x, 1.0 / n_root));
            break;
        }
        default: cout << "  [!] Gecersiz secim\n";
    }
}

void moduleStats() {
    printHeader("ISTATISTIK");
    int n = getInt("  Kac adet sayi gireceksiniz? ");
    if (n <= 0) { cout << "  [!] En az 1 sayi gerekli\n"; return; }

    vector<double> data(n);
    for (int i = 0; i < n; i++)
        data[i] = getDouble("  Sayi [" + to_string(i+1) + "]: ");

    sort(data.begin(), data.end());

    double sum = accumulate(data.begin(), data.end(), 0.0);
    double mean = sum / n;

    double variance = 0;
    for (double d : data) variance += (d - mean) * (d - mean);
    variance /= n;
    double stddev = sqrt(variance);

    double median;
    if (n % 2 == 0) median = (data[n/2 - 1] + data[n/2]) / 2.0;
    else             median = data[n/2];

    double q1 = data[n / 4];
    double q3 = data[3 * n / 4];

    cout << "\n  ┌──────────────────────────────────────┐\n";
    cout << "  │  ISTATISTIK SONUCLARI                 │\n";
    cout << "  ├──────────────────────────────────────┤\n";
    cout << fixed << setprecision(6);
    cout << "  │  Adet          : " << n             << "\n";
    cout << "  │  Toplam        : " << sum           << "\n";
    cout << "  │  Ortalama      : " << mean          << "\n";
    cout << "  │  Medyan        : " << median        << "\n";
    cout << "  │  Standart Sap. : " << stddev        << "\n";
    cout << "  │  Varyans       : " << variance      << "\n";
    cout << "  │  Min           : " << data.front()  << "\n";
    cout << "  │  Max           : " << data.back()   << "\n";
    cout << "  │  Aralik        : " << data.back() - data.front() << "\n";
    cout << "  │  Q1            : " << q1            << "\n";
    cout << "  │  Q3            : " << q3            << "\n";
    cout << "  └──────────────────────────────────────┘\n";
}

void moduleConvert() {
    printHeader("SAYI SISTEMI DONUSUMLERI");
    cout << "  [1] Onluk -> Ikilk / Sekizlik / Onaltilik\n";
    cout << "  [2] Ikilk -> Onluk\n";
    cout << "  [3] Onaltilik -> Onluk\n\n";

    int ch = getInt("  Seciminiz: ");

    if (ch == 1) {
        long long n = getInt("  Onluk sayi: ");
        cout << "\n  Decimal   : " << dec << n << "\n";
        cout << "  Binary    : " << bitset<32>(n).to_string().substr(bitset<32>(n).to_string().find('1')) << "\n";
        cout << "  Octal     : " << oct << n << dec << "\n";
        cout << "  Hex       : " << uppercase << hex << n << dec << "\n";
    } else if (ch == 2) {
        string bin;
        cout << "  Ikilk sayi (ornek: 1011): ";
        cin >> bin;
        try {
            long long val = stoll(bin, nullptr, 2);
            cout << "\n  Onluk karsiligi: " << val << "\n";
        } catch (...) {
            cout << "  [!] Gecersiz ikilk sayi\n";
        }
    } else if (ch == 3) {
        string hex_str;
        cout << "  Onaltilik sayi (ornek: 1F3A): ";
        cin >> hex_str;
        try {
            long long val = stoll(hex_str, nullptr, 16);
            cout << "\n  Onluk karsiligi: " << val << "\n";
        } catch (...) {
            cout << "  [!] Gecersiz onaltilik sayi\n";
        }
    }
}

typedef vector<vector<double>> Matrix;

Matrix readMatrix(int rows, int cols, const string& name) {
    cout << "  " << name << " matrisini girin (" << rows << "x" << cols << "):\n";
    Matrix M(rows, vector<double>(cols));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            M[i][j] = getDouble("    M[" + to_string(i) + "][" + to_string(j) + "]: ");
    return M;
}

void printMatrix(const Matrix& M) {
    cout << "\n";
    for (auto& row : M) {
        cout << "  | ";
        for (double v : row)
            cout << setw(10) << fixed << setprecision(4) << v << "  ";
        cout << "|\n";
    }
    cout << "\n";
}

double det2(const Matrix& M) {
    return M[0][0]*M[1][1] - M[0][1]*M[1][0];
}

double det3(const Matrix& M) {
    return M[0][0]*(M[1][1]*M[2][2]-M[1][2]*M[2][1])
          -M[0][1]*(M[1][0]*M[2][2]-M[1][2]*M[2][0])
          +M[0][2]*(M[1][0]*M[2][1]-M[1][1]*M[2][0]);
}

void moduleMatrix() {
    printHeader("MATRIS ISLEMLERI");
    cout << "  Boyut secin: [1] 2x2   [2] 3x3\n\n";
    int dim = getInt("  Seciminiz: ") + 1;

    cout << "\n  [1] Toplama    [2] Cikarma\n";
    cout << "  [3] Carpma     [4] Determinant\n";
    cout << "  [5] Transpoze\n\n";
    int op = getInt("  Islem: ");

    if (op == 4) {
        Matrix A = readMatrix(dim, dim, "A");
        double d = (dim == 2) ? det2(A) : det3(A);
        showResult("det(A)", d);
    } else if (op == 5) {
        Matrix A = readMatrix(dim, dim, "A");
        Matrix T(dim, vector<double>(dim));
        for (int i = 0; i < dim; i++)
            for (int j = 0; j < dim; j++)
                T[j][i] = A[i][j];
        cout << "  Transpoze:";
        printMatrix(T);
    } else if (op >= 1 && op <= 3) {
        Matrix A = readMatrix(dim, dim, "A");
        Matrix B = readMatrix(dim, dim, "B");
        Matrix C(dim, vector<double>(dim, 0));

        if (op == 1) {
            for (int i = 0; i < dim; i++)
                for (int j = 0; j < dim; j++)
                    C[i][j] = A[i][j] + B[i][j];
            cout << "  A + B =";
        } else if (op == 2) {
            for (int i = 0; i < dim; i++)
                for (int j = 0; j < dim; j++)
                    C[i][j] = A[i][j] - B[i][j];
            cout << "  A - B =";
        } else {
            for (int i = 0; i < dim; i++)
                for (int j = 0; j < dim; j++)
                    for (int k = 0; k < dim; k++)
                        C[i][j] += A[i][k] * B[k][j];
            cout << "  A x B =";
        }
        printMatrix(C);
    }
}

void moduleComplex() {
    printHeader("KOMPLEKS SAYI ISLEMLERI");
    cout << "  [1] Toplama  [2] Cikarma  [3] Carpma  [4] Bolme\n";
    cout << "  [5] Buyukluk (|z|)        [6] Argument (aci)\n";
    cout << "  [7] Esdeger (conjugate)   [8] Kuvvet\n\n";
    int ch = getInt("  Seciminiz: ");

    if (ch >= 1 && ch <= 4) {
        double r1 = getDouble("  z1 reel kisim   : ");
        double i1 = getDouble("  z1 sanal kisim  : ");
        double r2 = getDouble("  z2 reel kisim   : ");
        double i2 = getDouble("  z2 sanal kisim  : ");
        complex<double> z1(r1, i1), z2(r2, i2), res;
        string lbl;
        switch (ch) {
            case 1: res = z1 + z2; lbl = "z1 + z2"; break;
            case 2: res = z1 - z2; lbl = "z1 - z2"; break;
            case 3: res = z1 * z2; lbl = "z1 * z2"; break;
            case 4:
                if (abs(z2) == 0) { cout << "  [!] Sifira bolme\n"; return; }
                res = z1 / z2; lbl = "z1 / z2"; break;
        }
        cout << "\n  " << lbl << " = " << fixed << setprecision(6)
             << res.real() << (res.imag() >= 0 ? " + " : " - ")
             << fabs(res.imag()) << "i\n";
    } else if (ch == 5) {
        double r = getDouble("  Reel kisim : ");
        double i = getDouble("  Sanal kisim: ");
        showResult("|z|", abs(complex<double>(r, i)));
    } else if (ch == 6) {
        double r = getDouble("  Reel kisim : ");
        double i = getDouble("  Sanal kisim: ");
        cout << "\n  arg(z) = " << fixed << setprecision(6)
             << arg(complex<double>(r, i)) << " rad\n";
    } else if (ch == 7) {
        double r = getDouble("  Reel kisim : ");
        double i = getDouble("  Sanal kisim: ");
        cout << "\n  conj(z) = " << r << ((-i) >= 0 ? " + " : " - ")
             << fabs(i) << "i\n";
    } else if (ch == 8) {
        double r = getDouble("  Reel kisim : ");
        double i = getDouble("  Sanal kisim: ");
        double n = getDouble("  Kuvvet n   : ");
        complex<double> res = pow(complex<double>(r, i), n);
        cout << "\n  z^n = " << fixed << setprecision(6)
             << res.real() << (res.imag() >= 0 ? " + " : " - ")
             << fabs(res.imag()) << "i\n";
    }
}

void moduleUnits() {
    printHeader("BIRIM DONUSUMLERI");
    cout << "  [1] Uzunluk    [2] Alan       [3] Hacim\n";
    cout << "  [4] Kitle      [5] Sicaklik   [6] Hiz\n";
    cout << "  [7] Enerji     [8] Basinc\n\n";
    int cat = getInt("  Kategori: ");
    double val = getDouble("  Deger girin: ");

    cout << fixed << setprecision(6) << "\n";
    switch (cat) {
        case 1:
            cout << "  metre      : " << val << "\n";
            cout << "  kilometre  : " << val / 1000.0 << "\n";
            cout << "  santimetre : " << val * 100.0  << "\n";
            cout << "  milimetre  : " << val * 1000.0 << "\n";
            cout << "  inc        : " << val * 39.3701 << "\n";
            cout << "  fit        : " << val * 3.28084 << "\n";
            cout << "  mil        : " << val / 1609.34 << "\n";
            break;
        case 2:
            cout << "  m^2        : " << val << "\n";
            cout << "  km^2       : " << val / 1e6   << "\n";
            cout << "  cm^2       : " << val * 1e4   << "\n";
            cout << "  donum      : " << val / 1000.0 << "\n";
            cout << "  hektar     : " << val / 10000.0 << "\n";
            cout << "  ft^2       : " << val * 10.7639 << "\n";
            break;
        case 3:
            cout << "  litre      : " << val << "\n";
            cout << "  mililitre  : " << val * 1000.0  << "\n";
            cout << "  m^3        : " << val / 1000.0  << "\n";
            cout << "  galon(US)  : " << val * 0.264172 << "\n";
            cout << "  pint       : " << val * 2.11338 << "\n";
            break;
        case 4:
            cout << "  kilogram   : " << val << "\n";
            cout << "  gram       : " << val * 1000.0  << "\n";
            cout << "  ton        : " << val / 1000.0  << "\n";
            cout << "  pound      : " << val * 2.20462 << "\n";
            cout << "  ons        : " << val * 35.274  << "\n";
            break;
        case 5: {
            cout << "  Giris Celsius kabul edildi.\n";
            double C = val;
            cout << "  Fahrenheit : " << C * 9.0/5.0 + 32  << "\n";
            cout << "  Kelvin     : " << C + 273.15         << "\n";
            cout << "  Rankine    : " << (C + 273.15) * 9.0/5.0 << "\n";
            break;
        }
        case 6:
            cout << "  m/s        : " << val << "\n";
            cout << "  km/sa      : " << val * 3.6    << "\n";
            cout << "  mil/sa     : " << val * 2.23694 << "\n";
            cout << "  knot       : " << val * 1.94384 << "\n";
            cout << "  mach       : " << val / 343.0 << "\n";
            break;
        case 7:
            cout << "  Joule      : " << val << "\n";
            cout << "  kilojoule  : " << val / 1000.0 << "\n";
            cout << "  kalori     : " << val / 4.184  << "\n";
            cout << "  kWh        : " << val / 3.6e6  << "\n";
            cout << "  eV         : " << val / 1.602e-19 << "\n";
            break;
        case 8:
            cout << "  Pascal     : " << val << "\n";
            cout << "  kPa        : " << val / 1000.0 << "\n";
            cout << "  bar        : " << val / 1e5    << "\n";
            cout << "  atm        : " << val / 101325.0 << "\n";
            cout << "  psi        : " << val / 6894.76 << "\n";
            break;
        default: cout << "  [!] Gecersiz secim\n";
    }
}

void moduleConstants() {
    printHeader("FIZIKSEL & MATEMATIKSEL SABITLER");
    cout << fixed << setprecision(10);
    cout << "\n  -- Matematiksel --\n";
    cout << "  pi (pi)            = " << PI            << "\n";
    cout << "  e  (Euler)         = " << E_NUM          << "\n";
    cout << "  fi (Altin oran)    = " << PHI            << "\n";
    cout << "  sqrt(2)            = " << sqrt(2.0)      << "\n";
    cout << "  sqrt(3)            = " << sqrt(3.0)      << "\n";

    cout << "\n  -- Fiziksel --\n";
    cout << setprecision(6) << scientific;
    cout << "  c  (Isik hizi)     = " << 2.99792458e8   << " m/s\n";
    cout << "  g  (Yerc. ivmesi)  = " << 9.80665e0      << " m/s^2\n";
    cout << "  G  (Yerc. sabiti)  = " << 6.67430e-11    << " N m^2/kg^2\n";
    cout << "  h  (Planck)        = " << 6.62607015e-34 << " J s\n";
    cout << "  k  (Boltzmann)     = " << 1.380649e-23   << " J/K\n";
    cout << "  e  (Elektron yuku) = " << 1.602176634e-19 << " C\n";
    cout << "  me (Elektron kut.) = " << 9.1093837015e-31 << " kg\n";
    cout << "  Na (Avogadro)      = " << 6.02214076e23  << " mol^-1\n";
    cout << "  R  (Gaz sabiti)    = " << 8.314462618    << " J/(mol K)\n";
    cout << "\n";
}

void mainMenu() {
    printHeader("ANA MENU");
    cout << "  [1]  Temel Islemler\n";
    cout << "  [2]  Trigonometri\n";
    cout << "  [3]  Logaritma & Kuvvet\n";
    cout << "  [4]  Istatistik\n";
    cout << "  [5]  Sayi Sistemi Donusumleri\n";
    cout << "  [6]  Matris Islemleri (2x2 / 3x3)\n";
    cout << "  [7]  Kompleks Sayi Islemleri\n";
    cout << "  [8]  Birim Donusumleri\n";
    cout << "  [9]  Fiziksel & Matematiksel Sabitler\n";
    cout << "  [0]  Cikis\n\n";
}

int main() {
    int choice;
    do {
        mainMenu();
        choice = getInt("  Seciminiz: ");
        switch (choice) {
            case 1: moduleBasic();     break;
            case 2: moduleTrig();      break;
            case 3: moduleLogPow();    break;
            case 4: moduleStats();     break;
            case 5: moduleConvert();   break;
            case 6: moduleMatrix();    break;
            case 7: moduleComplex();   break;
            case 8: moduleUnits();     break;
            case 9: moduleConstants(); break;
            case 0:
                cout << "\n  Gorusuruz!\n\n";
                break;
            default:
                cout << "  [!] Gecersiz secim, tekrar deneyin.\n";
        }
        if (choice != 0) {
            cout << "\n  Devam etmek icin Enter'a basin...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    } while (choice != 0);

    return 0;
}
