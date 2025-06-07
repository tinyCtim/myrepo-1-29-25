
# fix line 8 to "Till it's ..." for the palindrome to work
my $verse = "
To her I flee; fine position. Trap all up, 
I won hat, last ewe, kilt, rat sets, a tooth, 
Self, no wars. I, lion, a leg? Nay. 
Men impugn in rub mill: animal spirit, 
Safe buoy, no main. I won't. In if fits? No. 
Is sap a spill? Later. I fall asleep 
Till H's a help mission. On back! 
Curtsey fixes her, eh? Sex if yes; 
Truck cab, no. No is simple. Ha! Still, it peels, 
All afire, tall lips, a passion stiff in it. 
Now! In! I am on you! Be fast! I rip! 
Slam In all! I'm burning up! Mine! My angel! 
An oil is raw on flesh, too; tastes tart, 
Like wet salt. Ah, now I pull apart! 
No, it is open. I feel fire: hot.
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
print "original:", $verse, "\n";
print "reverse :", $rverse, "\n";
$xor = $verse ^ $rverse;  # XOR with its reverse
$xor =~ s/[^\0]/\x20/g;  # "Flag" mismatches with \x20 in preparation for toupper case
# $xor =~ tr/\0/./;  # Remove null characters
$mismatches = $verse ^ $xor;  # XOR to show mismatches as uppercase
print "mismatch:", $mismatches, "\n";
