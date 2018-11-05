#This function is akin to matlab's linspace
sub linspace {
   my $n1=$_[2]-1;
   #my @rng=(0 .. $n1);
   #print "@rng\n";
   my $out=[map { $_ * ($_[1]-$_[0])/$n1 + $_[0] } (0 .. $n1)];
   #print "@$out\n";
   return $out;
}

#logspace(a,b,n) gives n values log base 10 spaced between a and b
sub logspace {
   my $out=[map {10**$_} (@{linspace(log($_[0])/log(10),log($_[1])/log(10),$_[2])})];
   #print "@$out\n";
   return $out;
}

1;
