
# fix line 8 to "Till it's ..." for the palindrome to work

my $verse = "
Able was I ere I saw Elba.
";

$verse = lc $verse; 
$verse =~ tr/a-z//cd;  # Remove non-alphabetic characters
$rverse = scalar reverse $verse;  # Reverse the verse
$palindrome = $verse eq $rverse;
if ($palindrome) {
    print "The verse is a palindrome.\n";
} else {
    print "The verse is not a palindrome.\n";
}
print $verse, "\n";
print $rverse, "\n";
$xor = $verse ^ $rverse;  # XOR with its reverse
$xor =~ s/[^\0]/x/g;  # Remove non-alphabetic characters
$xor =~ tr/\0/./;  # Remove null characters
print $xor, "\n";
