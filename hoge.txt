{ pkgs ? import <nixpkgs> {} }:
let
  lib = pkgs.lib;
  stdenv = pkgs.stdenv;
  python3 = pkgs.python3;
  fetchFromGitHub = pkgs.fetchFromGitHub;
  makeWrapper = pkgs.makeWrapper;
  gdb = pkgs.gdb;
  splitmind = import ./nix/splitmind.nix {
    inherit
      fetchFromGitHub
      stdenv;
  };
  pwndbg = import ./nix/pwndbg.nix {
    inherit
      fetchFromGitHub
      gdb
      makeWrapper
      python3
      lib
      splitmind
      stdenv;
  };
in
  pkgs.mkShell {
    nativeBuildInputs = [
      pwndbg
      pkgs.audacity
      pkgs.iperf
      pkgs.gnuplot
      pkgs.nettools
      pkgs.sox
    ];
  }
