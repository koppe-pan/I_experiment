{ stdenv
, fetchFromGitHub
}:

stdenv.mkDerivation rec {
  pname = "splitmind";
  version = "2022.04.28";
  format = "other";

  src = fetchFromGitHub {
    owner = "jerdna-regeiz";
    repo = "splitmind";
    rev = "a95b50f308f6e78b15c1fae9ed11239a6b70bdb7";
    sha256 = "sha256-RsPU8tmBjQevAdGU5WgPRsxvPe5gZ+TU07Ol4oYCWaU=";
  };

  installPhase = ''
    mkdir -p $out/share/splitmind
    cp -r . $out/share/splitmind
    chmod +x $out/share/splitmind/gdbinit.py
  '';
}
