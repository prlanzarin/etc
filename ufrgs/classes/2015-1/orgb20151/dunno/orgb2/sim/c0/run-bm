#!/usr/bin/perl

use warnings;
use strict;

my $prog_dir = "../../build";
my $out_dir = "benchs";
my $m2s_cmd = "m2s --x86-config ../base-x86-conf.conf --x86-sim detailed --mem-config ../base-mem-config.conf ";
`mkdir -p $out_dir`;

foreach my $prog (`ls $prog_dir`) {
    chomp $prog;
    my $out_filename = $out_dir . "/" . $prog . "-base" . ".sim";
    print "processando $out_filename\n";
    my $full_cmd = $m2s_cmd .
                   " ${prog_dir}/$prog" .
                   "1>/dev/null 2>" . $out_filename;
#        print $full_cmd . "\n";
    `$full_cmd`;
    }