#include <stdio.h>
#include <string.h>

int is_palindrome(const char *str) {
    int left = 0;
    int right = strlen(str) - 1;

    while (left < right) {
        if (str[left] != str[right]) {
            return 0;  // Not a palindrome
        }
        left++;
        right--;
    }

    return 1;  // Is a palindrome
}

int main() {
    char input[1000];

// toherifleefinepositiontrapallupiwonhatlastewekiltratsetsatoothselfnowarsilionalegnaymenimpugninrubmillanimalspiritsafebuoynomainiwontiniffitsnoissapaspilllaterifallasleeptillhsahelpmissiononbackcurtseyfixesherehsexifyestruckcabnonoissimplehastillitpeelsallafiretalllipsapassionstiffinitnowiniamonyoubefastiripslaminallimburningupminemyangelanoilisrawonfleshtootastestartlikewetsaltahnowipullapartnoitisopenifeelfirehot

    // Read input string
    if (scanf("%999s", input) == 1) {
        printf("%d\n", is_palindrome(input));
    } else {
        // Error reading input
        printf("0\n");
    }

    return 0;
}

