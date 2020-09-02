package xs;

use strict;
use warnings;

use Exporter qw<import>;
our @EXPORT_OK = qw<eval_str eval_file>;

use xs::scan qw<scan>;
use xs::parse qw<parse>;
use xs::ast qw<ast_print>;

use DDP;

sub eval_str {
  my ($str) = @_;

  my $x = parse(scan($str));
  print ast_print($x), "\n";
  $x;
}

sub eval_file {
  my ($f) = @_;
  open my $fh, '<', $f or die "Unable to open file $f: $!";
  my $str = do { local $/; <$fh>; };
  close $fh;
  eval_str($str);
}

420;
