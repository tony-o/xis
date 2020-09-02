package xs::ast;

use strict;
use warnings;

use Exporter qw<import>;
our @EXPORT_OK = qw<ast_print>;

sub ast_print {
  shift if ref $_[0] eq 'xs::scan';
  my ($structure) = @_;
#  use DDP; p $structure;
#  printf "%s\n", ref $structure;
  my $build = '';
  if (ref $structure eq 'ARRAY') {
    $build .= '(' . join(' ', (map { ast_print($_) } $structure->@*)) . ')';
  } else {
    $build .= $structure->{token};
  }
  $build;
}

69;
