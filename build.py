from pathlib import Path

import pycraft
import pycraft.cli

CWD = Path(__file__).parent

PROJ = pycraft.config.ProjectConfig(
    name="test",
    flags=pycraft.config.CompileFlags(
        cc=pycraft.config.Compiler.GCC,
        lang=pycraft.config.Language.C,
        version=17,
        opt=pycraft.config.OptimizeLevel.O0,
        dbg=pycraft.config.DebugLevel.G0,
        out_type=pycraft.config.OutputType.EXECUTABLE,
        includes=(CWD, ),
    ),
    src_dir=CWD / "_test",
    out_dir=CWD / "build",
)


if __name__ == "__main__":
    pycraft.init()
    assert pycraft.config.get_version() >= 3

    BUILD_CFG = pycraft.cli.get_build_config()
    # PROJ.flags.generate_compile_flags(Path("compile_flags.txt"))

    builder = pycraft.Builder(PROJ, BUILD_CFG)
    TARGET = builder.build()

    if BUILD_CFG.should_run():
        pycraft.run_project(TARGET)
