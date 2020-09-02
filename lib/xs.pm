package xs;

use strict;
use warnings;

use Exporter qw<import>;
our @EXPORT_OK = qw<eval_str eval_file>;

use xs::scan qw<scan>;
use xs::parse qw<parse>;
use xs::runner qw<runner>;
use xs::ast qw<ast_print>;

use DDP;

sub eval_str {
  my ($str) = @_;

  my @scan = scan($str);
  my @pars = [parse(\@scan)];
  printf "%s\n", ast_print(\@pars);
  runner(\@pars);
}

sub eval_file {
  my ($f) = @_;
  open my $fh, '<', $f or die "Unable to open file $f: $!";
  my $str = do { local $/; <$fh>; };
  close $fh;
  eval_str($str);
}

420;
