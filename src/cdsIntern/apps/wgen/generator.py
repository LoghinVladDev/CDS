from sys import argv
import json
from datetime import datetime, date
from pathlib import Path


platform_dependent_templates = [
    ("MSVC", {
        "macroIdentifier": {"start": "#if defined(_MSC_VER)", "mid": "#else // if defined(_MSC_VER)",
                            "end": "#endif // if defined(_MSC_VER)"},
        "parameters": "_warningName",
        "enable": [
            "__pragma(warning(push))",
            "__pragma(warning(disable:_warningName))"
        ], "disable": [
            "__pragma(warning(pop))"
        ]
    })
]

log_file = None
generation_step = -1


class GenerationStep:
    START = 0
    AUTHORSHIP = 1
    INCLUDE_GUARDS = 2
    PLATFORM_DEPENDENT_MACROS = 3
    PLATFORM_INDEPENDENT_MACROS = 4
    PLATFORM_DEPENDENT_CONFIG = 5
    PLATFORM_INDEPENDENT_CONFIG = 6
    END_INCLUDE_GUARDS = 7
    END = 8


def generation_step_name() -> str:
    return {
        GenerationStep.START: "Start of Generation",
        GenerationStep.AUTHORSHIP: "Writing Authorship",
        GenerationStep.INCLUDE_GUARDS: "Writing First Include Guard",
        GenerationStep.PLATFORM_DEPENDENT_MACROS: "Writing Platform Dependent Macros",
        GenerationStep.PLATFORM_INDEPENDENT_MACROS: "Writing Platform Independent Macros",
        GenerationStep.PLATFORM_DEPENDENT_CONFIG: "Writing Platform Dependent Config",
        GenerationStep.PLATFORM_INDEPENDENT_CONFIG: "Writing Platform Independent Config",
        GenerationStep.END_INCLUDE_GUARDS: "Writing End Include Guard",
        GenerationStep.END: "End of Generation"
    }[generation_step]


def log(msg: str) -> None:
    global log_file
    log_file.write(f"[Operation : '{generation_step_name()}' - "
                   f"{date.today().strftime('%d/%m/%Y')} - {datetime.now().strftime('%H:%M:%S')}] <-> {msg}\n")


def execute_step_sign_authorship(config: dict, out_file) -> None:
    global generation_step
    generation_step = GenerationStep.AUTHORSHIP

    log('Starting Writing Authorship')
    out_file.writelines(s + "\n" for s in [
        "//",
        "// CDS Warning Suppression Extension Header - Do not modify this header directly",
        "//",
        "// Generated for CDS through Warning Suppression Generator Tool",
        "// Author: Loghin Vlad-Andrei - github.com/LoghinVladDev",
        f"// Generation Date: {date.today().strftime('%d/%m/%y')} - {datetime.now().strftime('%H:%M:%S')}",
        "// CDS Version - 0.0.2",
        "// Licenced under Project Licence - https://github.com/LoghinVladDev/CDS/blob/master/LICENSE",
        "//",
        "",
        ""
    ])
    log('Writing Authorship Done')

    execute_step_include_guards(config, out_file)


def execute_step_include_guards(config: dict, out_file) -> None:
    global generation_step
    generation_step = GenerationStep.INCLUDE_GUARDS

    log('Writing Begin Include Guards')
    out_file.writelines(s + '\n' for s in [
        "//// Start of Include Guards",
        "",
        "#ifndef CDS_" + str(config['name']).upper().replace(".", "_"),
        "#define CDS_" + str(config['name']).upper().replace(".", "_"),
        "",
        "//// End of Include Guards",
        "",
        ""
    ])
    log('Finished Begin Include Guards')

    execute_step_platform_platform_dependant_macros(config, out_file)

    generation_step = GenerationStep.END_INCLUDE_GUARDS

    log('Writing End Include Guards')
    out_file.writelines(_ + "\n" for _ in [
        "//// Start of Include Guards",
        "",
        "#endif // CDS_" + str(config['name']).upper().replace(".", "_"),
        "",
        "//// End of Include Guards",
        "",
        ""
    ])


def execute_step_platform_platform_dependant_macros(config: dict, out_file) -> None:
    global generation_step
    generation_step = GenerationStep.PLATFORM_DEPENDENT_MACROS

    log('Start of Platform Dependent Macros')

    out_file.writelines(_ + "\n" for _ in [
        "//// Start of Platform Dependent Macros",
        "",
    ])

    for template in platform_dependent_templates:
        log(f"Applying Template for '{template[0]}'")
        out_file.writelines(_ + "\n" for _ in [
            template[1]["macroIdentifier"]["start"],
            "",
            "",
            f"#define __CDS_WarningSuppression_{template[0]}_SuppressEnable({template[1]['parameters']}) \\"
        ])

        enable_list = [s for s in template[1]["enable"]]

        for i in range(len(enable_list) - 1):
            enable_list[i] += " \\"

        out_file.writelines(_ + "\n" for _ in enable_list)
        out_file.writelines("\n")
        out_file.writelines(_ + "\n" for _ in [
            f"#define __CDS_WarningSuppression_{template[0]}_SuppressDisable({template[1]['parameters']}) \\"
        ])

        disable_list = [s for s in template[1]["disable"]]

        for i in range(len(disable_list) - 1):
            disable_list[i] += " \\"

        out_file.writelines(_ + "\n" for _ in disable_list)

        out_file.writelines(_ + "\n" for _ in [
            "", ""
        ])

        out_file.writelines(_ + "\n" for _ in [
            template[1]["macroIdentifier"]["mid"],
            ""
        ])

        out_file.writelines(_ + "\n" for _ in [
            "",
            f"#define __CDS_WarningSuppression_{template[0]}_SuppressEnable({template[1]['parameters']})",
            f"#define __CDS_WarningSuppression_{template[0]}_SuppressDisable({template[1]['parameters']})",
            "",
            ""
        ])

        out_file.writelines(_ + "\n" for _ in [
            template[1]["macroIdentifier"]["end"],
            ""
        ])

    out_file.writelines(_ + "\n" for _ in [
        "//// End of Platform Dependent Macros",
        "",
        ""
    ])

    log("Platform Dependent Macros End")
    execute_step_platform_platform_independent_macros(config, out_file)


def execute_step_platform_platform_independent_macros(config: dict, out_file) -> None:
    global generation_step
    generation_step = GenerationStep.PLATFORM_INDEPENDENT_MACROS

    log("Start of Platform Independent Macros")

    out_file.writelines(_ + "\n" for _ in [
        "//// Start of Platform Independent Macros", ""
    ])

    out_file.writelines(_ + "\n" for _ in [
        "#define __CDS_WarningSuppression_Platform_SuppressEnable(_platform, _warning)"
        " __CDS_WarningSuppression_ ## _platform ## _ ## _warning ## _SuppressEnable",
        "#define __CDS_WarningSuppression_Platform_SuppressDisable(_platform, _warning)"
        " __CDS_WarningSuppression_ ## _platform ## _ ## _warning ## _SuppressDisable",
        ""
    ])

    out_file.writelines(_ + "\n" for _ in [
        "//// End of Platform Independent Macros", "", ""
    ])

    log("End of Platform Independent Macros")
    execute_step_platform_platform_dependent_configured_rules(config, out_file)


def execute_step_platform_platform_dependent_configured_rules(config: dict, out_file) -> None:
    global generation_step
    generation_step = GenerationStep.PLATFORM_DEPENDENT_CONFIG

    log("Start of Platform Dependent Config Macros")
    out_file.writelines("//// Start of Platform Dependent Config Macros\n\n")

    for platform in config['platforms']:
        for warning in config['warnings']:
            if platform["name"] in warning.keys():
                out_file.writelines(_ + "\n" for _ in [
                    "#define __CDS_WarningSuppression_" + platform["name"] + "_" + warning["Name"] + "_SuppressEnable"
                    " __CDS_WarningSuppression_" + platform["name"] + "_SuppressEnable(" +
                    str(warning[platform["name"]]) + ")",
                    "#define __CDS_WarningSuppression_" + platform["name"] + "_" + warning["Name"] + "_SuppressDisable"
                    " __CDS_WarningSuppression_" + platform["name"] + "_SuppressDisable(" +
                    str(warning[platform["name"]]) + ")",
                    ""
                ])
            else:
                out_file.writelines(_ + "\n" for _ in [
                    "#define __CDS_WarningSuppression_" + platform["name"] + "_" + warning["Name"] + "_SuppressEnable",
                    "#define __CDS_WarningSuppression_" + platform["name"] + "_" + warning["Name"] + "_SuppressDisable",
                    ""
                ])

                # print(config)

    out_file.writelines("\n#define __CDS_WarningSuppression_SuppressEnable(_warning) \\\n")
    for i in range(len(config['platforms'])):
        out_file.writelines(f"\t__CDS_WarningSuppression_Platform_SuppressEnable({config['platforms'][i]['name']}"
                            f", _warning)")
        if i < len(config['platforms']) - 1:
            out_file.writelines('\\')
        out_file.writelines('\n')

    out_file.writelines("\n#define __CDS_WarningSuppression_SuppressDisable(_warning) \\\n")
    for i in range(len(config['platforms'])):
        out_file.writelines(f"\t__CDS_WarningSuppression_Platform_SuppressDisable({config['platforms'][i]['name']}"
                            f", _warning)")
        if i < len(config['platforms']) - 1:
            out_file.writelines('\\')
        out_file.writelines('\n')

    out_file.writelines("\n//// End of Platform Dependent Config Macros\n\n\n")
    log("End of Platform Dependent Config Macros")

    execute_step_platform_platform_independent_configured_rules(config, out_file)


def execute_step_platform_platform_independent_configured_rules(config: dict, out_file) -> None:
    global generation_step
    generation_step = GenerationStep.PLATFORM_INDEPENDENT_CONFIG

    log('Start of Platform Independent Config Macros')
    out_file.writelines("//// Start of Platform Dependent Config Macros\n\n")

    for warning in config['warnings']:
        out_file.writelines(_ + '\n' for _ in [
            f"#define __CDS_WarningSuppression_{warning['Name']}_SuppressEnable"
            f" __CDS_WarningSuppression_SuppressEnable({warning['Name']})",
            f"#define __CDS_WarningSuppression_{warning['Name']}_SuppressDisable"
            f" __CDS_WarningSuppression_SuppressDisable({warning['Name']})",
            ""
        ])

    out_file.writelines("//// End of Platform Dependent Config Macros\n\n\n")
    log('End of Platform Independent Config Macros')


def generate_header(config_path: str) -> None:
    global log_file
    global generation_step
    generation_step = GenerationStep.START
    log_file = open('log.txt', 'w')

    log('Starting Header Generation')

    log('Reading Configuration File')
    config = json.load(open(config_path, 'r'))
    log('Read Configuration File')

    log('Creating Output File')
    out_file = open(str(Path(config['dirpath']) / config['name']), 'w')
    log('Output File Created')

    execute_step_sign_authorship(config, out_file)

    out_file.close()
    log('Closed Output File')

    log('Done')
    log_file.close()


if __name__ == '__main__':
    if len(argv) < 2 or not argv[1].endswith('.json'):
        print('Requires configuration .json file')
        exit(0)

    generate_header(argv[1])