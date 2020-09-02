package xs::core;

use strict;
use warnings;

use Exporter qw<import>;
our @EXPORT_OK = qw<defenv>;

use DDP;

my $macro = {};
$macro = {
  '=' => sub {
    my ($args, $env, $runner) = @_;
    die '=: requires more than 1 argument' unless scalar $args->@* > 1;
    my ($x, $b) = $runner->(shift @$args);
    for (@$args) {
      $b = ($x eq $runner->($_)) ? 1 : 0;
      return 0 unless $b;
    }
    $b;
  },
  '<' => sub {
    my ($args, $env, $runner) = @_;
    die '<: requires more than 1 argument' unless scalar $args->@* > 1;
    my ($x, $b) = $runner->(shift @$args);
    for (@$args) {
      $b = ($x lt $runner->($_)) ? 1 : 0;
    }
    $b;
  },
  '<=' => sub {
    my ($args, $env, $runner) = @_;
    die '<: requires more than 1 argument' unless scalar $args->@* > 1;
    my ($x, $b) = $runner->(shift @$args);
    for (@$args) {
      $b = ($x le $runner->($_)) ? 1 : 0;
    }
    $b;
  },
  '>' => sub {
    $macro->{'<='}->(@_);
  },
  '>=' => sub {
    $macro->{'<'}->(@_);
  },
  '+' => sub {
    my ($args, $env, $runner) = @_;
    die '=: requires more than 1 argument' unless scalar $args->@* > 1;
    my $x = $runner->(shift @$args);
    for (@$args) {
      $x += $runner->($_);
    }
    $x;
  },
  'and' => sub {
    my ($args, $env, $runner) = @_;
    die 'and: requires at least one argument' unless scalar $args->@* >= 1;
    my $x = $runner->(shift @$args);
    for (@$args) {
      $x = ($x && $runner->($_)) ? 1 : 0;
      return 0 unless $x;
    }
    1;
  },
  'or' => sub {
    my ($args, $env, $runner) = @_;
    die 'and: requires at least one argument' unless scalar $args->@* >= 1;
    my $x = $runner->(shift @$args);
    for (@$args) {
      $x = ($x || $runner->($_)) ? 1 : 0;
    }
    $x;
  },
  'if' => sub {
    my ($args, $env, $runner) = @_;
    die 'if: requires three arguments' unless scalar $args->@* == 3;
    if ($runner->($args->[0])) {
      return $runner->($args->[1]);
    }
    $runner->($args->[2]);
  },
  'printf' => sub {
    my ($args, $env, $runner) = @_;
    die 'printf: requires at least one argument' unless scalar $args->@* >= 1;
    my @pf = map { $runner->($_) } @$args;
    printf(shift @pf, @pf);
    undef;
  },
  'def' => sub {
    my ($args, $env, $runner) = @_;
    my @lr = ((shift @$args)->{token}, $runner->(@$args));
    die 'def: requires exactly two arguments' unless @lr == 2;
    $env->set(@lr);
  },
};

sub defenv {
  $macro;
}

420;
