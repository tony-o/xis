package xs::env;

use strict;
use warnings;

use Exporter qw<import>;
our @EXPORT_OK = qw<new>;

sub new {
  bless {
    data   => ($_[1]//{}),
    parent => ($_[2]//undef),
  }, $_[0];
}

sub get {
  my ($self, $var) = @_;
  unless (exists $self->{data}->{$var}) {
    die "variable $var not available in current scope"
      unless ref $self->{parent} eq 'xs::env';
    return $self->{parent}->get($var);
  }
  $self->{data}->{$var};
}

sub set {
  my ($self, $var, $val) = @_;
  $self->{data}->{$var} = $val;
}

sub dump {
  my ($self) = @_;
  {
    (ref $self->{parent} eq 'xs::env' ? ($self->{parent}->dump->%*) : ()),
    $self->{data},
  };
}

69;
