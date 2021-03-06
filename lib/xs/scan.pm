package xs::scan;

use strict;
use warnings;

use feature 'switch';
no warnings 'experimental';

use Exporter qw<import>;
our @EXPORT_OK = qw<scan>;

sub scan {
  my @src = split '', $_[ref $_[0] eq 'xs::scan' ? 1 : 0];
  my ($pos, $line, $c, $take, $tok, $type) = (0,1,0,0,);
  my @tokens;
  $take = @src;
  while ($c < @src) {
    $tok  = shift @src;
    $type = 'IGNORE';
    given ($tok) {
      when (($tok . join('', @src)) =~ m{^(fun|macro|def)\s*:}) {
        $tok = $1;
        @src = @src[(length($&) - 1) ..@src - 1];
        $type = 'DECLARATION';
      }
      when ($tok ge '0' && $tok le '9' || (($tok eq '.' || $tok eq '-') && $src[0] ge '0' && $src[0] le '9')) {
        if (join('', @src) =~ m{^\d+\.?\d*}) {
          $tok  = $tok . $&;
          @src  = @src[length($&) ..@src - 1];
        }
        $type = 'NUMBER';
      }
      when ($tok =~ m{^[a-zA-Z_=><!\-\?0-9]$}) {
        join('', @src) =~ m{^[a-zA-Z_=><!\-\?0-9]*};
        $type = 'SYMBOL';
        $tok  = $tok . $&;
        @src  = @src[length($&) ..@src - 1];
      }
      when ($tok eq '"' || $tok eq "'") {
        my $m;
        if ($tok eq '"') {
          join('', @src) =~ m{^.*(?<!\\)"}g;
          $m = $&;
        } else {
          join('', @src) =~  m{^.*(?<!\\)'}g;
          $m = $&;
        }
        $tok  = substr($m, 0, length($m) - 1);
        @src  = @src[length($m) .. @src - 1];
        $type = 'STRING';
      }
      when ($tok eq "\n") {
        $line++;
        $pos = -1;
        $type = 'NEWLINE';
      }
      when ($tok eq ' ') {
        join('', @src) =~ m/^[ ]*/;
        @src  = @src[length($&) .. @src - 1];
        $tok .= $&;
        $type = 'SPACE';
      }
      when ($tok eq '#') {
        while ($src[0] ne "\n") {
          $tok .= shift @src;
        }
        $pos = -1;
        $line++;
        $type = 'COMMENT';
      }
      when ($tok =~ m{[!\$\%\&\|\*\+-/:<=>\?\@^_~,]}) {
        $tok  = $&;
        if ($tok eq '=' && (($src[0]//'') eq '>' || ($src[0]//'') eq '<')) {
          $tok .= shift @src;
        }
        $type = 'CONTROL';
      }
      default { 
        printf "Unexpected character '%s' line(%s) pos(%s)\n", $tok, $line, $pos;
        exit 128;
      };
    };
    if ($type ne 'IGNORE') {
      push @tokens, {
        type  => $type,
        token => "$tok",
        line  => $line,
        pos   => $pos,
      };
      $pos += $take - @src;
      $take = @src;
    } else {
      $pos++;
    }
  }
  push @tokens, { type => 'EOF', token => '', line => $line, pos => $pos };
  @tokens;
}

69;
