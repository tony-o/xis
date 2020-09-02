package xs::parse;

use strict;
use warnings;

use Exporter qw<import>;
our @EXPORT_OK = qw<parse>;

sub _eat {
  my ($idx, $type, $tokens, $ignore) = @_;
  my $i = $idx;
  $ignore //= qr{.*};
  while ($tokens->[$i]->{type} =~ $type && $i < scalar @$tokens) {
    die sprintf("Unexpected %s (%s) @ %d, %d",
                $tokens->[$i]->{type},
                $tokens->[$i]->{token},
                $tokens->[$i]->{line},
                $tokens->[$i]->{pos},
               )
      if $tokens->[$i]->{type} !~ $ignore
      && $i < scalar @$tokens;
    $i++;
  }
  die 'Unexpected end of input' unless $i < scalar @$tokens;
  $i;
}

sub parse {
  shift if ref $_[0] eq 'xs::parse';
  my ($tokens) = @_;
  my $build    = '';
  my $idx      = 0;
  # lispy out
  my ($tok, $nxt, $expr, @lpos, $spos, $i);
  $expr   = [];
  @lpos   = 0;
  my $ptr = [$expr];
  $i = 0;
  $spos = $tokens->[0]->{pos}//-1;
  while ($idx < $tokens->@*) {
    $idx++, next if $tokens->[$idx]->{type} =~ m{^(SPACE|EOF|COMMENT)$};
    $tok = $tokens->[$idx];
    #printf "I:%d LPOS:%s IDX:%d LINE:%d POS:%d TYPE:%s TOKEN:%s\n", ($i++), (join(',', @lpos)//'nil'), $idx, $tok->{line}, $tok->{pos}, $tok->{type}, ($tok->{type} eq 'NEWLINE' ? "<nl>" : $tok->{token});
    if ($tok->{type} eq 'DECLARATION') {
      my $a = [{%$tok, type=>'CALL'}];
      push @{$ptr->[-1]}, $a;
      push @$ptr, $a;
      push @lpos, $spos;
    } elsif ($tok->{type} eq 'SYMBOL' || ($tok->{type} eq 'CONTROL' && $tok->{token} !~ m{^(,)$})) {
      $i = _eat($idx+1, qr{^(?!NEWLINE|SPACE)$}, $tokens);
      $nxt = $tokens->[$i];
      if ($nxt->{type} eq 'CONTROL' && $nxt->{token} eq ':') {
        push @lpos, $spos;
        my $a = [{%$tok, type=>'CALL'}];
        push @{$ptr->[-1]}, $a;
        push @$ptr, $a;
        $idx = $i + 1;
      } else {
        push @{$ptr->[-1]}, $tok;
      }
    } elsif ($tok->{type} eq 'NUMBER' || $tok->{type} eq 'STRING') {
      push @{$ptr->[-1]}, $tok;
    } elsif ($tok->{type} eq 'NEWLINE') {
      $i = _eat($idx+1, qr{^(?!NEWLINE|SPACE)$}, $tokens);
      $nxt = $tokens->[$i];
      $spos = $nxt->{pos};
      while ($nxt->{pos} < $lpos[-1] && @$ptr > 1) {
        pop @lpos;
        pop @$ptr;
      }
    } elsif ($tok->{type} eq 'CONTROL') {
      if ($tok->{token} eq ',') {
        pop @lpos;
        pop @$ptr;
        die sprintf("errant comma? line(%d) pos(%d)", $tok->{line}, $tok->{pos}) if @$ptr == 0;
      }
    }
    $idx++;
  }
  $expr;
}

69;
