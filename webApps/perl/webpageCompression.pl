#!/usr/bin/perl
use warnings;
use strict;

use LWP::Simple;
use Compress::Zlib;

print "Please provide the first well-formed URL: ";
my $firstPage = <>;
chomp $firstPage;
print "Please provide the second well-formed URL: ";

my $secondPage = <>;
chomp $secondPage;

my $firstContent = get($firstPage);
my $secondContent = get($secondPage);
my $resultContent = $firstContent . $secondContent;
$resultContent = compress($resultContent);
$firstContent = compress($firstContent);
$secondContent = compress($secondContent);

my $firstLength = length $firstContent;
my $secondLength = length $secondContent;
my $resultLength = length $resultContent;

my $maxLength;
my $minLength;

if ($firstLength > $secondLength) {
	$maxLength = $firstLength;
	$minLength = $secondLength;
}
else {
	$maxLength = $secondLength;
        $minLength = $firstLength;
}

my $NCD = ($resultLength - $minLength)/$maxLength;

print "Similarity score: " . $NCD . "\n";
