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
        cout << "  [!] Invalid input. Please enter a number.\n";
    }
}

int getInt(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) return val;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  [!] Invalid input. Please enter an integer.\n";
    }
}

void showResult(const string& label, double result, int precision = 10) {
    cout << "\n  ┌─────────────────────────────────────┐\n";
    cout << "  │  " << left << setw(14) << label
         << " = " << right << fixed << setprecision(precision) << result << "\n";
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
    cout << "  ║         CALCULATOR — C++                 ║\n";
    cout << "  ╠══════════════════════════════════════════╣\n";
    cout << "  ║  " << left << setw(42) << title << "║\n";
    cout << "  ╚══════════════════════════════════════════╝\n\n";
}

void moduleBasic() {
    printHeader("BASIC OPERATIONS");
    cout << "  [1] Addition        [2] Subtraction\n";
    cout << "  [3] Multiplication  [4] Division\n";
    cout << "  [5] Power (x^y)     [6] Remainder (mod)\n";
    cout << "  [7] Rounding (floor/ceil/round)\n";
    cout << "  [0] Main Menu\n\n";

    int ch = getInt("  Your choice: ");
    if (ch == 0) return;

    if (ch >= 1 && ch <= 6) {
        double a = getDouble("  First number:  ");
        double b = getDouble("  Second number: ");
        switch (ch) {
            case 1: showResult("Sum", a + b); break;
            case 2: showResult("Difference", a - b); break;
            case 3: showResult("Product", a * b); break;
            case 4:
                if (b == 0) { cout << "  [!] Division by zero error!\n"; }
                else        { showResult("Quotient", a / b); }
                break;
            case 5: showResult("Power", pow(a, b)); break;
            case 6:
                if (b == 0) { cout << "  [!] Modulo by zero error!\n"; }
                else        { showResult("Remainder", fmod(a, b)); }
                break;
        }
    } else if (ch == 7) {
        double a = getDouble("  Number: ");
        cout << "\n  floor(" << a << ") = " << floor(a) << "\n";
        cout << "  ceil (" << a << ") = " << ceil(a)  << "\n";
        cout << "  round(" << a << ") = " << round(a) << "\n";
    } else {
        cout << "  [!] Invalid choice.\n";
    }
}

void moduleTrig() {
    printHeader("TRIGONOMETRY");
    cout << "  In which unit would you like to enter angles?\n";
    cout << "  [1] Degrees   [2] Radians\n\n";
    int unit = getInt("  Your choice: ");

    cout << "\n  [1] sin    [2] cos    [3] tan\n";
    cout << "  [4] asin   [5] acos   [6] atan\n";
    cout << "  [7] sinh   [8] cosh   [9] tanh\n";
    cout << "  [10] atan2(y, x)\n\n";
    int ch = getInt("  Function: ");

    double deg2rad = (unit == 1) ? PI / 180.0 : 1.0;

    if (ch >= 1 && ch <= 9) {
        double a = getDouble("  Value: ");
        double rad = a * deg2rad;
        switch (ch) {
            case 1: showResult("sin", sin(rad)); break;
            case 2: showResult("cos", cos(rad)); break;
            case 3:
                if (fabs(cos(rad)) < 1e-12) cout << "  [!] Tangent is undefined at this angle!\n";
                else showResult("tan", tan(rad));
                break;
            case 4:
                if (a < -1.0 || a > 1.0) cout << "  [!] asin domain is [-1, 1]\n";
                else showResult("asin (rad)", asin(a));
                break;
            case 5:
                if (a < -1.0 || a > 1.0) cout << "  [!] acos domain is [-1, 1]\n";
                else showResult("acos (rad)", acos(a));
                break;
            case 6: showResult("atan (rad)", atan(a)); break;
            case 7: showResult("sinh", sinh(rad)); break;
            case 8: showResult("cosh", cosh(rad)); break;
            case 9: showResult("tanh", tanh(rad)); break;
        }
    } else if (ch == 10) {
        double y = getDouble("  y value: ");
        double x = getDouble("  x value: ");
        showResult("atan2 (rad)", atan2(y, x));
    } else {
        cout << "  [!] Invalid choice.\n";
    }
}

void moduleLogPow() {
    printHeader("LOGARITHM & POWER");
    cout << "  [1] ln(x)          [2] log10(x)\n";
    cout << "  [3] log_b(x)       [4] e^x\n";
    cout << "  [5] 10^x           [6] sqrt(x)\n";
    cout << "  [7] cbrt(x)        [8] x! (factorial)\n";
    cout << "  [9] n-th root\n\n";

    int ch = getInt("  Your choice: ");
    double x, b;

    switch (ch) {
        case 1:
            x = getDouble("  x: ");
            if (x <= 0) cout << "  [!] ln undefined (x must be > 0)\n";
            else showResult("ln(x)", log(x));
            break;
        case 2:
            x = getDouble("  x: ");
            if (x <= 0) cout << "  [!] log10 undefined (x must be > 0)\n";
            else showResult("log10(x)", log10(x));
            break;
        case 3:
            b = getDouble("  Base b: ");
            x = getDouble("  x: ");
            if (b <= 0 || b == 1.0 || x <= 0)
                cout << "  [!] Invalid values (b > 0, b != 1, x > 0)\n";
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
            if (x < 0) cout << "  [!] Square root of negative number is undefined (Real)\n";
            else showResult("sqrt(x)", sqrt(x));
            break;
        case 7:
            x = getDouble("  x: ");
            showResult("cbrt(x)", cbrt(x));
            break;
        case 8: {
            int n = getInt("  n (n <= 20 recommended): ");
            if (n < 0) { cout << "  [!] Factorial of negative number is undefined\n"; break; }
            if (n > 20) { cout << "  [!] n too large, overflow risk (max 20)\n"; break; }
            long long fact = 1;
            for (int i = 2; i <= n; i++) fact *= i;
            cout << "\n  " << n << "! = " << fact << "\n";
            break;
        }
        case 9: {
            double n_root = getDouble("  Root degree (n): ");
            x = getDouble("  x: ");
            if (n_root == 0.0) { cout << "  [!] Root degree cannot be 0\n"; break; }
            showResult("n-th root", pow(x, 1.0 / n_root));
            break;
        }
        default: cout << "  [!] Invalid choice.\n";
    }
}

void moduleStats() {
    printHeader("STATISTICS");
    int n = getInt("  How many numbers will you enter? ");
    if (n <= 0) { cout << "  [!] At least 1 number is required\n"; return; }

    vector<double> data(n);
    for (int i = 0; i < n; i++)
        data[i] = getDouble("  Number [" + to_string(i + 1) + "]: ");

    sort(data.begin(), data.end());

    double sum = accumulate(data.begin(), data.end(), 0.0);
    double mean = sum / n;

    double variance = 0;
    for (double d : data) variance += (d - mean) * (d - mean);
    variance /= n;
    double stddev = sqrt(variance);

    double median;
    if (n % 2 == 0) median = (data[n / 2 - 1] + data[n / 2]) / 2.0;
    else             median = data[n / 2];

    // Proper quartile calculation
    double q1, q3;
    int lower_half = n / 2;
    if (n % 2 == 0) {
        q1 = (lower_half % 2 == 0)
             ? (data[lower_half / 2 - 1] + data[lower_half / 2]) / 2.0
             : data[lower_half / 2];
        q3 = (lower_half % 2 == 0)
             ? (data[n / 2 + lower_half / 2 - 1] + data[n / 2 + lower_half / 2]) / 2.0
             : data[n / 2 + lower_half / 2];
    } else {
        q1 = (lower_half % 2 == 0)
             ? (data[lower_half / 2 - 1] + data[lower_half / 2]) / 2.0
             : data[lower_half / 2];
        q3 = (lower_half % 2 == 0)
             ? (data[n / 2 + 1 + lower_half / 2 - 1] + data[n / 2 + 1 + lower_half / 2]) / 2.0
             : data[n / 2 + 1 + lower_half / 2];
    }

    cout << "\n  ┌──────────────────────────────────────┐\n";
    cout << "  │  STATISTICS RESULTS                  │\n";
    cout << "  ├──────────────────────────────────────┤\n";
    cout << fixed << setprecision(6);
    cout << "  │  Count         : " << n             << "\n";
    cout << "  │  Sum           : " << sum           << "\n";
    cout << "  │  Mean          : " << mean          << "\n";
    cout << "  │  Median        : " << median        << "\n";
    cout << "  │  Std Deviation : " << stddev        << "\n";
    cout << "  │  Variance      : " << variance      << "\n";
    cout << "  │  Min           : " << data.front()  << "\n";
    cout << "  │  Max           : " << data.back()   << "\n";
    cout << "  │  Range         : " << data.back() - data.front() << "\n";
    cout << "  │  Q1            : " << q1            << "\n";
    cout << "  │  Q3            : " << q3            << "\n";
    cout << "  └──────────────────────────────────────┘\n";
}

void moduleConvert() {
    printHeader("NUMBER SYSTEM CONVERSIONS");
    cout << "  [1] Decimal  -> Binary / Octal / Hexadecimal\n";
    cout << "  [2] Binary   -> Decimal\n";
    cout << "  [3] Hex      -> Decimal\n\n";

    int ch = getInt("  Your choice: ");

    if (ch == 1) {
        long long n = (long long)getDouble("  Decimal number: ");
        cout << "\n  Decimal   : " << dec << n << "\n";
        if (n >= 0) {
            // Trim leading zeros from binary
            string binStr = bitset<64>(n).to_string();
            size_t firstOne = binStr.find('1');
            cout << "  Binary    : " << (firstOne == string::npos ? "0" : binStr.substr(firstOne)) << "\n";
        } else {
            cout << "  Binary    : (negative — two's complement 64-bit: " << bitset<64>(n) << ")\n";
        }
        cout << "  Octal     : " << oct << n << dec << "\n";
        cout << "  Hex       : " << uppercase << hex << n << dec << "\n";
    } else if (ch == 2) {
        string bin;
        cout << "  Binary number (e.g. 1011): ";
        cin >> bin;
        // Validate binary string
        bool valid = !bin.empty();
        for (char c : bin) if (c != '0' && c != '1') { valid = false; break; }
        if (!valid) {
            cout << "  [!] Invalid binary number\n";
        } else {
            try {
                long long val = stoll(bin, nullptr, 2);
                cout << "\n  Decimal equivalent: " << val << "\n";
            } catch (...) {
                cout << "  [!] Number out of range\n";
            }
        }
    } else if (ch == 3) {
        string hex_str;
        cout << "  Hexadecimal number (e.g. 1F3A): ";
        cin >> hex_str;
        // Validate hex string
        bool valid = !hex_str.empty();
        for (char c : hex_str)
            if (!isxdigit((unsigned char)c)) { valid = false; break; }
        if (!valid) {
            cout << "  [!] Invalid hexadecimal number\n";
        } else {
            try {
                long long val = stoll(hex_str, nullptr, 16);
                cout << "\n  Decimal equivalent: " << val << "\n";
            } catch (...) {
                cout << "  [!] Number out of range\n";
            }
        }
    } else {
        cout << "  [!] Invalid choice.\n";
    }
}

typedef vector<vector<double>> Matrix;

Matrix readMatrix(int rows, int cols, const string& name) {
    cout << "  Enter matrix " << name << " (" << rows << "x" << cols << "):\n";
    Matrix M(rows, vector<double>(cols));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            M[i][j] = getDouble("    M[" + to_string(i) + "][" + to_string(j) + "]: ");
    return M;
}

void printMatrix(const Matrix& M) {
    cout << "\n";
    for (const auto& row : M) {
        cout << "  | ";
        for (double v : row)
            cout << setw(10) << fixed << setprecision(4) << v << "  ";
        cout << "|\n";
    }
    cout << "\n";
}

double det2(const Matrix& M) {
    return M[0][0] * M[1][1] - M[0][1] * M[1][0];
}

double det3(const Matrix& M) {
    return M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1])
          - M[0][1] * (M[1][0] * M[2][2] - M[1][2] * M[2][0])
          + M[0][2] * (M[1][0] * M[2][1] - M[1][1] * M[2][0]);
}

void moduleMatrix() {
    printHeader("MATRIX OPERATIONS");
    cout << "  Select size: [1] 2x2   [2] 3x3\n\n";
    int sel = getInt("  Your choice: ");

    // Fix: originally used sel+1 which gave wrong dimension for choice 1 (2) and choice 2 (3)
    int dim;
    if (sel == 1) dim = 2;
    else if (sel == 2) dim = 3;
    else { cout << "  [!] Invalid choice.\n"; return; }

    cout << "\n  [1] Addition     [2] Subtraction\n";
    cout << "  [3] Multiplication  [4] Determinant\n";
    cout << "  [5] Transpose\n\n";
    int op = getInt("  Operation: ");

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
        cout << "  Transpose:";
        printMatrix(T);
    } else if (op >= 1 && op <= 3) {
        Matrix A = readMatrix(dim, dim, "A");
        Matrix B = readMatrix(dim, dim, "B");
        Matrix C(dim, vector<double>(dim, 0.0));

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
    } else {
        cout << "  [!] Invalid choice.\n";
    }
}

void moduleComplex() {
    printHeader("COMPLEX NUMBER OPERATIONS");
    cout << "  [1] Addition   [2] Subtraction  [3] Multiplication  [4] Division\n";
    cout << "  [5] Magnitude (|z|)              [6] Argument (angle)\n";
    cout << "  [7] Conjugate                    [8] Power\n\n";
    int ch = getInt("  Your choice: ");

    if (ch >= 1 && ch <= 4) {
        double r1 = getDouble("  z1 real part      : ");
        double i1 = getDouble("  z1 imaginary part : ");
        double r2 = getDouble("  z2 real part      : ");
        double i2 = getDouble("  z2 imaginary part : ");
        complex<double> z1(r1, i1), z2(r2, i2), res(0, 0);
        string lbl;
        switch (ch) {
            case 1: res = z1 + z2; lbl = "z1 + z2"; break;
            case 2: res = z1 - z2; lbl = "z1 - z2"; break;
            case 3: res = z1 * z2; lbl = "z1 * z2"; break;
            case 4:
                if (abs(z2) == 0.0) { cout << "  [!] Division by zero\n"; return; }
                res = z1 / z2; lbl = "z1 / z2"; break;
        }
        cout << "\n  " << lbl << " = " << fixed << setprecision(6)
             << res.real() << (res.imag() >= 0 ? " + " : " - ")
             << fabs(res.imag()) << "i\n";
    } else if (ch == 5) {
        double r = getDouble("  Real part      : ");
        double i = getDouble("  Imaginary part : ");
        showResult("|z|", abs(complex<double>(r, i)));
    } else if (ch == 6) {
        double r = getDouble("  Real part      : ");
        double i = getDouble("  Imaginary part : ");
        cout << "\n  arg(z) = " << fixed << setprecision(6)
             << arg(complex<double>(r, i)) << " rad\n";
    } else if (ch == 7) {
        double r = getDouble("  Real part      : ");
        double i = getDouble("  Imaginary part : ");
        double neg_i = -i;
        cout << "\n  conj(z) = " << fixed << setprecision(6)
             << r << (neg_i >= 0 ? " + " : " - ")
             << fabs(i) << "i\n";
    } else if (ch == 8) {
        double r = getDouble("  Real part      : ");
        double i = getDouble("  Imaginary part : ");
        double n = getDouble("  Power n        : ");
        complex<double> res = pow(complex<double>(r, i), n);
        cout << "\n  z^n = " << fixed << setprecision(6)
             << res.real() << (res.imag() >= 0 ? " + " : " - ")
             << fabs(res.imag()) << "i\n";
    } else {
        cout << "  [!] Invalid choice.\n";
    }
}

void moduleUnits() {
    printHeader("UNIT CONVERSIONS");
    cout << "  [1] Length     [2] Area       [3] Volume\n";
    cout << "  [4] Mass       [5] Temperature [6] Speed\n";
    cout << "  [7] Energy     [8] Pressure\n\n";
    int cat = getInt("  Category: ");
    double val = getDouble("  Enter value: ");

    cout << fixed << setprecision(6) << "\n";
    switch (cat) {
        case 1:
            cout << "  metres       : " << val << "\n";
            cout << "  kilometres   : " << val / 1000.0   << "\n";
            cout << "  centimetres  : " << val * 100.0    << "\n";
            cout << "  millimetres  : " << val * 1000.0   << "\n";
            cout << "  inches       : " << val * 39.3701  << "\n";
            cout << "  feet         : " << val * 3.28084  << "\n";
            cout << "  miles        : " << val / 1609.34  << "\n";
            break;
        case 2:
            cout << "  m^2          : " << val << "\n";
            cout << "  km^2         : " << val / 1e6      << "\n";
            cout << "  cm^2         : " << val * 1e4      << "\n";
            cout << "  acres        : " << val / 4046.86  << "\n";
            cout << "  hectares     : " << val / 10000.0  << "\n";
            cout << "  ft^2         : " << val * 10.7639  << "\n";
            break;
        case 3:
            cout << "  litres       : " << val << "\n";
            cout << "  millilitres  : " << val * 1000.0   << "\n";
            cout << "  m^3          : " << val / 1000.0   << "\n";
            cout << "  US gallons   : " << val * 0.264172 << "\n";
            cout << "  pints        : " << val * 2.11338  << "\n";
            break;
        case 4:
            cout << "  kilograms    : " << val << "\n";
            cout << "  grams        : " << val * 1000.0   << "\n";
            cout << "  tonnes       : " << val / 1000.0   << "\n";
            cout << "  pounds       : " << val * 2.20462  << "\n";
            cout << "  ounces       : " << val * 35.274   << "\n";
            break;
        case 5: {
            cout << "  Input treated as Celsius.\n";
            double C = val;
            cout << "  Fahrenheit   : " << C * 9.0 / 5.0 + 32.0     << "\n";
            cout << "  Kelvin       : " << C + 273.15                 << "\n";
            cout << "  Rankine      : " << (C + 273.15) * 9.0 / 5.0  << "\n";
            break;
        }
        case 6:
            cout << "  m/s          : " << val << "\n";
            cout << "  km/h         : " << val * 3.6      << "\n";
            cout << "  mph          : " << val * 2.23694  << "\n";
            cout << "  knots        : " << val * 1.94384  << "\n";
            cout << "  mach         : " << val / 343.0    << "\n";
            break;
        case 7:
            cout << "  Joules       : " << val << "\n";
            cout << "  kilojoules   : " << val / 1000.0   << "\n";
            cout << "  calories     : " << val / 4.184    << "\n";
            cout << "  kWh          : " << val / 3.6e6    << "\n";
            cout << "  eV           : " << val / 1.602e-19 << "\n";
            break;
        case 8:
            cout << "  Pascals      : " << val << "\n";
            cout << "  kPa          : " << val / 1000.0   << "\n";
            cout << "  bar          : " << val / 1e5      << "\n";
            cout << "  atm          : " << val / 101325.0 << "\n";
            cout << "  psi          : " << val / 6894.76  << "\n";
            break;
        default: cout << "  [!] Invalid choice.\n";
    }
}

void moduleConstants() {
    printHeader("PHYSICAL & MATHEMATICAL CONSTANTS");
    cout << fixed << setprecision(10);
    cout << "\n  -- Mathematical --\n";
    cout << "  pi  (Pi)               = " << PI          << "\n";
    cout << "  e   (Euler's number)   = " << E_NUM       << "\n";
    cout << "  phi (Golden ratio)     = " << PHI         << "\n";
    cout << "  sqrt(2)                = " << sqrt(2.0)   << "\n";
    cout << "  sqrt(3)                = " << sqrt(3.0)   << "\n";

    cout << "\n  -- Physical --\n";
    cout << setprecision(6) << scientific;
    cout << "  c  (Speed of light)    = " << 2.99792458e8    << " m/s\n";
    cout << "  g  (Gravity)           = " << 9.80665e0       << " m/s^2\n";
    cout << "  G  (Grav. constant)    = " << 6.67430e-11     << " N m^2/kg^2\n";
    cout << "  h  (Planck)            = " << 6.62607015e-34  << " J s\n";
    cout << "  k  (Boltzmann)         = " << 1.380649e-23    << " J/K\n";
    cout << "  e  (Electron charge)   = " << 1.602176634e-19 << " C\n";
    cout << "  me (Electron mass)     = " << 9.1093837015e-31 << " kg\n";
    cout << "  Na (Avogadro)          = " << 6.02214076e23   << " mol^-1\n";
    cout << "  R  (Gas constant)      = " << 8.314462618     << " J/(mol K)\n";
    cout << "\n";
}

void mainMenu() {
    printHeader("MAIN MENU");
    cout << "  [1]  Basic Operations\n";
    cout << "  [2]  Trigonometry\n";
    cout << "  [3]  Logarithm & Power\n";
    cout << "  [4]  Statistics\n";
    cout << "  [5]  Number System Conversions\n";
    cout << "  [6]  Matrix Operations (2x2 / 3x3)\n";
    cout << "  [7]  Complex Number Operations\n";
    cout << "  [8]  Unit Conversions\n";
    cout << "  [9]  Physical & Mathematical Constants\n";
    cout << "  [0]  Exit\n\n";
}

int main() {
    int choice;
    do {
        mainMenu();
        choice = getInt("  Your choice: ");
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
                cout << "\n  Goodbye!\n\n";
                break;
            default:
                cout << "  [!] Invalid choice, please try again.\n";
        }
        if (choice != 0) {
            cout << "\n  Press Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    } while (choice != 0);

    return 0;
}
