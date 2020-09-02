package xs::runner;

use strict;
use warnings;

use Exporter qw<import>;
our @EXPORT_OK = qw<runner>;

use xs::env;
use xs::core qw<defenv>;

use DDP;
my $x = 0;
sub runner {
  shift if ref $_[0] eq 'xs::runner';
  my ($structure, $parenv) = @_;
  my $env = $parenv // xs::env->new(defenv);
  my $wra = sub {
    my @a = @_;
    runner(@a, $env);
  };

  if (ref $structure eq 'ARRAY') {
    if (ref $structure->[0] ne 'ARRAY'
    &&  ($structure->[0]->{type} eq 'CALL')) {
      my $nm = (shift @$structure)->{token};
      my $fn = $env->get($nm);
      die "No such function '$nm' in environment" unless $fn;
      my $l = $fn->($structure, $env, $wra);
      return $l;
    } else {
      my @l;
      for my $s ($structure->@*) {
        push @l, $wra->($s);
      }
      return \@l;
    }
  } elsif ($structure->{type}) {
    my $str = $structure->{token} // '';
    $str =~ s/\\n/\n/g if $structure->{type} eq 'STRING';
    return $str if $structure->{type} eq 'NUMBER'
                || $structure->{type} eq 'STRING';
    return $env->get($structure->{token});
  }

#  if (ref $structure eq 'ARRAY') {
#    my $idx = 0;
#    while ($idx < @$structure) {
#      my $s = $structure->[$idx];
#      if (ref $s eq 'ARRAY' && ref $s->[0] ne 'ARRAY') {
#        my $nm = (shift @$s)->{token};
#        my $fn = $env->get($nm);
#        die "No such function '$nm' in environment" unless $fn;
#        my $l = $fn->($s, $env, $wra);
#        return $l if scalar @$structure == 1;
#      } else {
#        return runner($s, $env, $wra);
#      }
#      $idx++;
#    }
#  } else {
#    my $str = $structure->{token} // '';
#    $str =~ s/\\n/\n/g if $structure->{type} eq 'STRING';
#    return $str if $structure->{type} eq 'NUMBER'
#                || $structure->{type} eq 'STRING';
#    return $env->get($structure->{token});
#  }
}

69;
