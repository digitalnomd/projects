#!/usr/bin/perl
use warnings;
use strict;

use LWP::Simple;

print "Enter a well-formed URL: ";
my $page = <STDIN>;
chomp $page;
print "The following are links found on " . $page . "\n";
#store the contents in a buffer
my $content = get($page);
#parse the href tags and store in an array
my @links = $content =~ /<a href="(http[^"]+)/gi;

#print out all the links in the arrray
foreach my $link (@links) {
	print $link . "\n";
}

