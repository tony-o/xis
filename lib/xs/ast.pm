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
    $build .= '(' if ref $structure->[0] ne 'ARRAY';
    $build .= join(' ', (map { ast_print($_) } $structure->@*));
    $build .= ")" if ref $structure->[0] ne 'ARRAY';
  } else {
    $build .= '"' if $structure->{type} eq 'STRING';
    $build .= $structure->{token};
    $build .= '"' if $structure->{type} eq 'STRING';
  }
  $build;
}

69;
