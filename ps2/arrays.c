#include <stdio.h>

float roundTo(float, int);
unsigned long binom_coef(int, int);

float lift_a_car(const int stick_length, const int human_weight, const int car_weight) {
    float result = stick_length * human_weight / (float) (human_weight + car_weight);
    return roundTo(result, 2);
}

float unit_price(const float pack_price, const int rolls_count, const int pieces_count) {
    float result = (100.0f * pack_price) / (rolls_count * pieces_count);
    return roundTo(result, 2);
}

int bank_notes(const int price) {
    int notes[] = { 200, 100, 50, 20, 10 };
    int notes_count = 0;
    int temp_price = price;

    for(int i = 0; i < 5; ++i) {
        notes_count += temp_price / notes[i];
        temp_price %= notes[i];
    }

    if(temp_price != 0) {
        return -1;
    }

    return notes_count;
}

int euler(const int n) {
    float prime_count = n;
    int num = n;
    int last_divider = 0;

    while(num > 1) {
        int divider = 2;
        while(num % divider != 0) {
            divider++;
        }
        if(divider > last_divider) {
            prime_count *= 1.0f - 1.0f / (float) divider;
        }
        num /= divider;
        last_divider = divider;
    }

    return (int) roundTo(prime_count, 0);
}

int find_missing_number(const int n, const int arr[]) {
    int sum = 0;
    for(int i = 0; i < n; ++i) {
        sum += arr[i];
    }

    int valid_sum = ((n + 1) * n) / 2;
    return valid_sum - sum;
}

unsigned long sum_squared(const int line) {
    unsigned long sum = 0;
    unsigned long coef;

    for(int j = 0; j <= line; ++j) {
        coef = binom_coef(line, j);
        sum += coef * coef;
    }

    return sum;
}

int array_min(const int input_array[], const int array_size) {
    if(!input_array || array_size <= 0) {
        return -1;
    }

    int min = input_array[0];
    for(int i = 0; i < array_size; ++i) {
        if(input_array[i] < min) {
            min = input_array[i];
        }
    }

    return min;
}

int array_max(const int input_array[], const int array_size) {
    if(!input_array || array_size <= 0) {
        return -1;
    }

    int max = input_array[0];
    for(int i = 0; i < array_size; ++i) {
        if(input_array[i] > max) {
            max = input_array[i];
        }
    }

    return max;
}

int factorize_count(const int n) {
    int num = n;
    int dividers_count = 0;
    int last_divider = 0;

    while(num > 1) {
        int divider = 2;
        while(num % divider != 0) {
            divider++;
        }
        if(divider > last_divider) {
            dividers_count++;
        }
        num /= divider;
        last_divider = divider;
    }

    return dividers_count;
}

void podium(const int n, int arr[]) {
    if(n < 3) {
        return;
    }

    int num = n;
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 0;
    num -= 3;

    for(int i = 0; i < 3; ++i) {
        arr[i] += num / 3;
    }

    int mod = num % 3;
    if(mod) {
        arr[1]++;
        if(mod == 2) {
            arr[0]++;
        } else if(arr[2] > 0) {
            arr[0]++;
            arr[2]--;
        }
    }
}

int main() {
    printf("Task1:\n");
    printf("%.4f\n", lift_a_car(2, 80, 1400));
    // prints: 0.1100
    printf("%.4f\n\n", lift_a_car(4, 90, 1650));
    // prints: 0.2100

    printf("Task2:\n");
    printf("%.4f\n", unit_price(4.79, 16, 150));
    // prints: 0.2000
    printf("%.4f\n\n", unit_price(5.63, 20, 200));
    // prints: 0.1400

    printf("Task3:\n");
    printf("%d\n", bank_notes(540));
    // prints: 5
    printf("%d\n\n", bank_notes(5));
    // prints: -1

    printf("Task4:\n");
    printf("%d\n", euler(6));
    // prints: 2
    printf("%d\n\n", euler(12));
    // prints: 4

    printf("Task5:\n");
    int input_array[] = {3,0,1};
    printf("%d\n\n", find_missing_number(3, input_array));
    // prints: 2

    printf("Task6:\n");
    printf("%lu\n", sum_squared(1));
    // prints: 2
    printf("%lu\n", sum_squared(4));
    // prints: 70
    printf("%lu\n\n", sum_squared(33));
    // prints: 7219428434016265740

    printf("Task7:\n");
    int input_array2[] = {1,2,3,4,5};
    printf("%d\n", array_min(input_array2, 5));
    // prints: 1
    printf("%d\n", array_max(input_array2, 5));
    // prints: 5
    printf("%d\n\n", array_max(NULL, 5));
    // prints: -1

    printf("Task8:\n");
    printf("%d\n\n", factorize_count(12));
    // prints: 2

    printf("Task9:\n");
    int heights[3];
    int material = 6;
    podium(material, heights);

    for(int i = 0; i < 3; i++){
        printf("%d ", heights[i]);
    }
    printf("\n");
    // prints: 2 3 1
}

float roundTo(const float number, const int digits) {
    if(digits < 0) {
        return number;
    }

    int multiplier = 1;
    for(int i = 0; i < digits; ++i) {
        multiplier *= 10;
    }

    float numberf = number * multiplier;
    float fractional = numberf - (int) numberf;

    if(fractional <= 0.5f) {
        return (int) numberf / (float) multiplier;
    }

    return ((int) numberf + 1) / (float) multiplier;
}

unsigned long binom_coef(const int n, const int m) {
    if(m == 0) {
        return 1;
    }

    if(n < m) {
        return 0;
    }

    int denominator = 2;
    unsigned long numerator = 1;
    for(int i = m + 1; i <= n; ++i) {
        numerator *= i;
        if(numerator % denominator == 0 && denominator <= n - m) {
            numerator /= denominator;
            denominator++;
        }
    }

    return numerator;
}