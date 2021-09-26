import json
import pathlib
import os

from sys import argv as program_arguments

from typing import Union, Any, List, Dict

from PyQt6.QtCore import QSize
from PyQt6.QtCore import Qt
from PyQt6.QtCore import QMetaObject
from PyQt6.QtCore import pyqtSignal as QSignal

from PyQt6.QtGui import QCloseEvent

from PyQt6.QtWidgets import QAbstractItemView
from PyQt6.QtWidgets import QApplication
from PyQt6.QtWidgets import QCheckBox
from PyQt6.QtWidgets import QComboBox
from PyQt6.QtWidgets import QFileDialog
from PyQt6.QtWidgets import QFrame
from PyQt6.QtWidgets import QHBoxLayout
from PyQt6.QtWidgets import QHeaderView
from PyQt6.QtWidgets import QLabel
from PyQt6.QtWidgets import QLayout
from PyQt6.QtWidgets import QLineEdit
from PyQt6.QtWidgets import QListWidget
from PyQt6.QtWidgets import QListWidgetItem
from PyQt6.QtWidgets import QMessageBox
from PyQt6.QtWidgets import QPushButton
from PyQt6.QtWidgets import QSizePolicy
from PyQt6.QtWidgets import QSpacerItem
from PyQt6.QtWidgets import QTableWidget
from PyQt6.QtWidgets import QTableWidgetItem
from PyQt6.QtWidgets import QVBoxLayout
from PyQt6.QtWidgets import QWidget

from generator import generate_header


class Platform:
    class WarningType:
        UNKNOWN: int = 0
        INTEGER: int = 1
        COMMENT: int = 2

        def __init__(self, value: int):
            if value < Platform.WarningType.UNKNOWN or value > Platform.WarningType.COMMENT:
                value = Platform.WarningType.UNKNOWN

            self.__value = value

        @property
        def value(self) -> int:
            return self.__value

        def __int__(self) -> int:
            return self.value

        def __str__(self) -> str:
            return {
                Platform.WarningType.UNKNOWN: 'Unknown',
                Platform.WarningType.INTEGER: 'Integer Value',
                Platform.WarningType.COMMENT: 'As Comment'
            }[self.value]

    def __init__(self, warning_type: int, platform_name: str):
        self.__warning_type: Platform.WarningType = Platform.WarningType(warning_type)
        self.__platform_name: str = platform_name

    @property
    def warning_type(self) -> WarningType:
        return self.__warning_type

    @warning_type.setter
    def warning_type(self, value: WarningType) -> None:
        self.__warning_type = value

    @property
    def platform_name(self) -> str:
        return self.__platform_name

    @platform_name.setter
    def platform_name(self, value: str) -> None:
        self.__platform_name = value

    def __str__(self) -> str:
        return f"""Platform ( name = {self.platform_name}, warning_type = '{str(self.warning_type)}' )"""


def all_platform_warning_types() -> List[Platform.WarningType]:
    return [
        Platform.WarningType(Platform.WarningType.INTEGER),
        Platform.WarningType(Platform.WarningType.COMMENT)
    ]


def base_platforms() -> List[Platform]:
    return [
        Platform(Platform.WarningType.INTEGER, 'MSVC')
    ]


class PlatformWindow(QWidget):
    closed = QSignal()

    def __init__(self, parent: QWidget = None, platforms: List[Platform] = None):
        super(QWidget, self).__init__(parent)

        self.__platforms = platforms.copy()
        self.__platforms_to_save = []

        self.setLayout(QVBoxLayout())

        mid_section: QLayout = QHBoxLayout()

        mid_section_labels: QLayout = QVBoxLayout()

        platform_name_label: QLabel = QLabel("""Platform Name""", self)
        platform_warning_suppress_label: QLabel = QLabel("""Warning Suppression Type""", self)

        mid_section_labels.addWidget(platform_name_label)
        mid_section_labels.addWidget(platform_warning_suppress_label)

        mid_section_labels.setAlignment(platform_name_label, Qt.AlignmentFlag.AlignBottom)
        mid_section_labels.setAlignment(platform_warning_suppress_label, Qt.AlignmentFlag.AlignTop)

        mid_section_edits: QLayout = QVBoxLayout()

        platform_name_input: QLineEdit = QLineEdit(self)
        platform_warning_suppress_input: QComboBox = QComboBox(self)

        for item in all_platform_warning_types():
            platform_warning_suppress_input.addItem(str(item), item)

        mid_section_edits.addWidget(platform_name_input)
        mid_section_edits.addWidget(platform_warning_suppress_input)

        mid_section_edits.setAlignment(platform_name_input, Qt.AlignmentFlag.AlignBottom)
        mid_section_edits.setAlignment(platform_warning_suppress_input, Qt.AlignmentFlag.AlignTop)

        mid_section_buttons: QLayout = QVBoxLayout()

        mid_section.addItem(mid_section_labels)
        mid_section.addItem(mid_section_edits)
        mid_section.addItem(mid_section_buttons)

        add_button: QPushButton = QPushButton("Add", self)
        add_button.setDisabled(True)

        remove_button: QPushButton = QPushButton("Remove", self)
        remove_button.setDisabled(True)

        mid_section_buttons.addWidget(add_button)
        mid_section_buttons.addItem(QSpacerItem(0, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum))
        mid_section_buttons.addWidget(remove_button)

        mid_section_buttons.setAlignment(add_button, Qt.AlignmentFlag.AlignBottom)
        mid_section_buttons.setAlignment(remove_button, Qt.AlignmentFlag.AlignTop)

        platform_list: QListWidget = QListWidget(self)

        mid_section.addWidget(platform_list)

        buttons_section: QLayout = QHBoxLayout()

        self.__ok_button: QPushButton = QPushButton('Ok', self)
        self.__cancel_button: QPushButton = QPushButton('Cancel', self)
        self.__apply_button: QPushButton = QPushButton('Apply', self)

        buttons_section.addWidget(self.ok_button)
        buttons_section.addWidget(self.cancel_button)
        buttons_section.addWidget(self.apply_button)

        self.ok_button.clicked.connect(lambda: self.ok())
        self.apply_button.clicked.connect(lambda: self.apply())
        self.cancel_button.clicked.connect(lambda: self.cancel())

        self.layout().addWidget(QLabel('Platforms', self))
        self.layout().addItem(mid_section)
        self.layout().addItem(buttons_section)

        platform_name_input.textChanged.connect(lambda content: add_button.setEnabled(len(content) > 0))

        def reset_inputs() -> None:
            platform_name_input.clear()
            platform_warning_suppress_input.setCurrentIndex(0)

        add_button.clicked.connect(lambda: self.add_platform(
            Platform(platform_warning_suppress_input.currentData().value, platform_name_input.text()), platform_list))
        add_button.clicked.connect(lambda: reset_inputs())

        for platform in self.platforms:
            self.add_platform(platform, platform_list)

        platform_list.setSelectionMode(QAbstractItemView.SelectionMode.SingleSelection)
        platform_list.itemSelectionChanged.connect(lambda: remove_button.setEnabled(True))

        self.apply_button.setDisabled(True)

        def remove_selected(window: PlatformWindow, list_widget: QListWidget) -> None:
            platform_to_remove = list_widget.itemWidget(list_widget.item(list_widget.currentRow())).to_platform()
            index_of_item = -1
            for i in range(len(window.__platforms_to_save)):
                if window.__platforms_to_save[i].platform_name == platform_to_remove.platform_name:
                    index_of_item = i

            if index_of_item != -1:
                window.__platforms_to_save.remove(window.__platforms_to_save[index_of_item])

            list_widget.takeItem(list_widget.currentRow())

            window.apply_button.setEnabled(window.apply_possible())

        remove_button.clicked.connect(lambda: remove_selected(self, platform_list))

    def add_platform(self, platform: Platform, widget_list: QListWidget) -> None:
        self.__platforms_to_save.append(platform)

        class PlatformListEntry(QWidget):
            def __init__(self, parent: QWidget = None, p_name: str = '',
                         p_type: Platform.WarningType = Platform.WarningType(Platform.WarningType.UNKNOWN)):
                super(QWidget, self).__init__(parent)

                self.__p_name = p_name
                self.__p_type = p_type

                self.__platform_name_label = QLabel(p_name, self)
                self.__platform_type_label = QLabel(f'Type : {p_type}', self)

                self.setLayout(QHBoxLayout())

                self.layout().addWidget(self.__platform_name_label)
                self.layout().addWidget(self.__platform_type_label)

            def to_platform(self) -> Platform:
                return Platform(warning_type=self.__p_type.value, platform_name=self.__p_name)

        container: QListWidgetItem = QListWidgetItem(widget_list)
        item: PlatformListEntry = PlatformListEntry(p_name=platform.platform_name, p_type=platform.warning_type,
                                                    parent=self)

        container.setSizeHint(item.sizeHint())

        widget_list.setItemWidget(container, item)
        self.apply_button.setEnabled(self.apply_possible())

    def apply_possible(self) -> bool:
        found: List[str] = []

        if len(self.platforms) != len(self.__platforms_to_save):
            return True

        for i in range(len(self.platforms)):
            found.append(self.platforms[i].platform_name)

        for i in range(len(self.__platforms_to_save)):
            if self.__platforms_to_save[i].platform_name not in found:
                return False
            else:
                found.remove(self.__platforms_to_save[i].platform_name)

        return len(found) != 0

    def apply(self) -> None:
        self.__platforms = self.__platforms_to_save.copy()
        self.apply_button.setDisabled(True)

    def cancel(self) -> None:
        self.close()

    def ok(self) -> None:
        self.apply()
        self.close()

    @property
    def ok_button(self) -> QPushButton:
        return self.__ok_button

    @property
    def cancel_button(self) -> QPushButton:
        return self.__cancel_button

    @property
    def apply_button(self) -> QPushButton:
        return self.__apply_button

    def closeEvent(self, a0: QCloseEvent) -> None:
        # noinspection PyUnresolvedReferences
        self.closed.emit()

    @property
    def platforms(self) -> List[Platform]:
        return self.__platforms


class GeneratorWindow(QWidget):
    def __init__(self, parent: QWidget = None):
        super(QWidget, self).__init__(parent)

        self.setWindowTitle('CDS Warnings Header Generator')

        self.setLayout(QVBoxLayout())

        self.layout().addWidget(QLabel("""CDS Warning Suppression Header Generator""", self))

        self.__header_name_input: QLineEdit = QLineEdit(self)
        self.__header_output_path_input: QLineEdit = QLineEdit(self)
        self.__header_output_path_selector: QPushButton = QPushButton("...", self)

        self.__force_bypass_notification = False

        self.__configuration_fields_layout: QLayout = QHBoxLayout()
        self.__configuration_path_input: QLineEdit = QLineEdit(self)
        self.__configuration_load_button: QPushButton = QPushButton("""Load...""", self)
        self.__configuration_save_button: QPushButton = QPushButton("""Save""", self)
        self.__configuration_save_as_button: QPushButton = QPushButton("""Save As...""", self)

        self.__warnings_table: QTableWidget = QTableWidget(self)
        self.__edit_platforms_button: QPushButton = QPushButton("""Edit Platforms...""", self)

        self.__warnings: List[Dict[str, str]] = []
        self.__header_list: List[str] = []

        self.__platforms: List[Platform] = base_platforms().copy()

        self.__force_disabled: bool = False

        self.__loaded_configuration = None
        self.__loaded_configuration_path: str = ''

        self.__warning_updates_disabled: bool = False

        # noinspection PyTypeChecker
        self.__window_on_top: PlatformWindow = None

        self.__use_configuration_checkbox: QCheckBox = QCheckBox('Use Configuration', self)

        self.add_separator_line()
        self.add_configuration_fields()

        self.add_separator_line()
        self.add_header_fields()

        self.add_separator_line()
        self.add_warning_fields()

        self.add_separator_line()
        self.add_generation_inputs()

        self.header_output_path_input.setText((str(pathlib.Path(__file__).parent.resolve() / 'output')))
        self.header_name_input.setText('Warnings.hpp')

        self.header_name_input.textChanged.connect(lambda: self.check_for_save_update())
        self.header_output_path_input.textChanged.connect(lambda: self.check_for_save_update())

        self.configuration_path_input.textChanged.connect(lambda: self.configuration_save_button.setEnabled(
            self.__loaded_configuration_path == self.__configuration_path_input.text()))

        self.resize(900, 600)

        self.use_configuration_checkbox.setChecked(True)
        self.__force_bypass_notification = True
        self.__configuration_path_input.setText('default_config.json')

    def add_separator_line(self) -> None:
        separator_line: QFrame = QFrame()
        separator_line.setFrameShape(QFrame.Shape.HLine)
        separator_line.setFrameShadow(QFrame.Shadow.Sunken)

        self.layout().addWidget(separator_line)

    @property
    def use_configuration_checkbox(self) -> QCheckBox:
        return self.__use_configuration_checkbox

    @property
    def warning_updates_disabled(self) -> bool:
        return self.__warning_updates_disabled

    @warning_updates_disabled.setter
    def warning_updates_disabled(self, value: bool) -> None:
        self.__warning_updates_disabled = value

    @property
    def platforms(self) -> List[Platform]:
        return self.__platforms

    @property
    def edit_platforms_button(self) -> QPushButton:
        return self.__edit_platforms_button

    @property
    def header_name_input(self) -> QLineEdit:
        return self.__header_name_input

    @property
    def force_bypass_notification(self) -> bool:
        value = self.__force_bypass_notification
        self.__force_bypass_notification = False
        return value

    @force_bypass_notification.setter
    def force_bypass_notification(self, value: bool) -> None:
        self.__force_bypass_notification = value

    @property
    def header_output_path_input(self) -> QLineEdit:
        return self.__header_output_path_input

    @property
    def header_output_path_selector(self) -> QPushButton:
        return self.__header_output_path_selector

    @property
    def configuration_fields_layout(self) -> QLayout:
        return self.__configuration_fields_layout

    @property
    def configuration_path_input(self) -> QLineEdit:
        return self.__configuration_path_input

    @property
    def configuration_load_button(self) -> QPushButton:
        return self.__configuration_load_button

    @property
    def configuration_save_button(self) -> QPushButton:
        return self.__configuration_save_button

    @property
    def configuration_save_as_button(self) -> QPushButton:
        return self.__configuration_save_as_button

    @property
    def warnings_table(self) -> QTableWidget:
        return self.__warnings_table

    @property
    def header_list(self) -> List[str]:
        return self.__header_list

    @property
    def warnings(self) -> List[Dict[str, str]]:
        return self.__warnings

    def enable_use_configuration(self) -> None:
        self.configuration_path_input.setEnabled(True)
        self.configuration_load_button.setEnabled(True)

    def disable_use_configuration(self) -> None:
        self.configuration_path_input.setDisabled(True)
        self.configuration_load_button.setDisabled(True)

        self.configuration_save_button.setDisabled(True)
        self.__loaded_configuration = None

    def add_configuration_fields(self) -> None:
        self.layout().addItem(self.configuration_fields_layout)

        self.use_configuration_checkbox.stateChanged.connect(lambda state:
                                                             self.enable_use_configuration()
                                                             if Qt.CheckState(state) == Qt.CheckState.Checked else
                                                             self.disable_use_configuration())

        self.configuration_fields_layout.addWidget(self.use_configuration_checkbox)
        self.configuration_fields_layout.addWidget(self.configuration_path_input)
        self.configuration_fields_layout.addWidget(self.configuration_load_button)
        self.configuration_fields_layout.addWidget(self.configuration_save_button)
        self.configuration_fields_layout.addWidget(self.configuration_save_as_button)

        self.configuration_save_button.setDisabled(True)

        self.disable_use_configuration()

        self.configuration_save_as_button.clicked.connect(lambda:
                                                          self.save_configuration(self.get_current_configuration()))

        self.configuration_load_button.clicked.connect(lambda: self.load_configuration_window())
        self.configuration_path_input.textChanged.connect(lambda: self.try_load_config(self.force_bypass_notification))

    def load_configuration_window(self) -> None:
        self.force_bypass_notification = True
        self.configuration_path_input.setText(QFileDialog.getOpenFileName(
            self, "Open Configuration File", str(pathlib.Path(__file__).parent.resolve()),
            "CDS Configuration (*.json);;All Files (*)"
        )[0])

    def load_config(self, config: dict, bypass_question: bool = False) -> None:
        for key in ['name', 'dirpath', 'platforms', 'warnings']:
            if key not in config.keys():
                return

        if not bypass_question:
            # noinspection PyTypeChecker
            if QMessageBox.StandardButton.Yes != QMessageBox.question(self, "Load Configuration?",
                                                                      "Configuration File Detected. Load File?",
                                                                      QMessageBox.StandardButton.Yes |
                                                                      QMessageBox.StandardButton.No,
                                                                      QMessageBox.StandardButton.No):
                return

        self.header_name_input.setText(config['name'])
        self.header_output_path_input.setText(config['dirpath'])
        self.platforms.clear()

        for p in config['platforms']:
            self.platforms.append(Platform(p['type'], p['name']))

        self.warnings.clear()

        for i in range(len(config['warnings'])):
            item: Dict[str, str] = {'Name': config['warnings'][i]['Name']}

            for platform in self.platforms:
                if platform.platform_name in config['warnings'][i].keys():
                    item[platform.platform_name] = str(config['warnings'][i][platform.platform_name])
                else:
                    item[platform.platform_name] = ''

            self.warnings.append(item)

        # self.configuration_save_button.setEnabled(True)

        self.__loaded_configuration = config.copy()
        self.configuration_save_button.clicked.connect(lambda:
                                                       self.save_to_file(self.get_current_configuration(),
                                                                         self.__loaded_configuration_path))

        self.update_platform_headers(bypass_save_enable=True)

    def try_load_config(self, bypass_question: bool = False) -> None:
        try:
            self.load_config(json.load(open(self.configuration_path_input.text(), 'r')), bypass_question)
            self.__loaded_configuration_path = self.configuration_path_input.text()

        except IOError:
            self.__loaded_configuration_path = ''
            pass

    def save_to_file(self, configuration: Union[Dict[str, Any], None], out_file_path: str) -> None:
        if configuration is None:
            return

        try:
            if not out_file_path:
                return

            file = open(out_file_path, 'w')
            json.dump(configuration, file, indent=4)
            file.close()

            QMessageBox.information(self, 'Success', 'Configuration Saved Successfully!',
                                    QMessageBox.StandardButton.Ok, QMessageBox.StandardButton.Ok)
        except IOError:
            QMessageBox.critical(self, 'Failure', 'Unexpected Error Occurred',
                                 QMessageBox.StandardButton.Ok, QMessageBox.StandardButton.Ok)

    def save_configuration(self, configuration: Union[Dict[str, Any], None]) -> None:
        self.save_to_file(configuration, QFileDialog.getSaveFileName(self, "Save Configuration",
                                                                     str(pathlib.Path(__file__).parent.resolve()),
                                                                     "CDS Configuration (*.json);;All Files (*)")[0])

    def add_header_fields(self) -> None:
        layout: QLayout = QHBoxLayout()

        self.layout().addItem(layout)

        labels_layout: QLayout = QVBoxLayout()
        line_edits_layout: QLayout = QVBoxLayout()

        layout.addItem(labels_layout)
        layout.addItem(line_edits_layout)

        labels_layout.addWidget(QLabel("""Header File Name""", self))
        labels_layout.addWidget(QLabel("""Output Path (relative to root of project)""", self))

        line_edits_layout.addWidget(self.header_name_input)

        path_edit_layout: QLayout = QHBoxLayout()
        path_edit_layout.addWidget(self.header_output_path_input)
        path_edit_layout.addWidget(self.header_output_path_selector)

        path_edit_layout.setAlignment(self.header_output_path_selector, Qt.AlignmentFlag.AlignRight)

        self.header_output_path_selector.setFixedSize(QSize(25, 25))

        line_edits_layout.addItem(path_edit_layout)

        self.header_output_path_selector.clicked.connect(lambda: self.open_path_selection_dialog())

    def closeEvent(self, a0: QCloseEvent) -> None:
        if self.window_on_top is not None:
            self.window_on_top.close()

    def open_path_selection_dialog(self) -> None:
        file_path: str = str(pathlib.Path(__file__).parent.resolve())
        file_path = file_path[:file_path.find('src') - 1]

        self.header_output_path_input.setText(QFileDialog.getExistingDirectory(self, "Open Directory", file_path,
                                                                               QFileDialog.Option.ShowDirsOnly |
                                                                               QFileDialog.Option.DontResolveSymlinks))

    @property
    def window_on_top(self) -> PlatformWindow:
        return self.__window_on_top

    @window_on_top.setter
    def window_on_top(self, value: PlatformWindow) -> None:
        self.__window_on_top = value

    @property
    def force_disabled(self) -> bool:
        return self.__force_disabled

    @force_disabled.setter
    def force_disabled(self, value: bool) -> None:
        self.__force_disabled = value

    def save_platforms_window_data(self, new_platforms: List[Platform]) -> None:
        change_detected = self.change_detected(new_platforms)

        self.__platforms = new_platforms
        self.update_platform_headers()
        self.close_platforms_window()

        if change_detected:
            self.check_for_save_update()

    def change_detected(self, new_platforms: List[Platform]) -> bool:
        names: List[str] = [i.platform_name for i in self.platforms]
        for i in new_platforms:
            if not names:
                return True

            for j in names:
                if i.platform_name == j:
                    names.remove(j)
                else:
                    return True

        return len(names) != 0

    def update_platform_headers(self, bypass_save_enable=False) -> None:
        self.__header_list: List[str] = ['', 'Name']
        for platform in self.platforms:
            self.header_list.append(platform.platform_name)

        self.__warnings_table.setColumnCount(len(self.header_list))
        self.__warnings_table.setHorizontalHeaderLabels(self.header_list)
        self.__warnings_table.horizontalHeader().setSectionResizeMode(0, QHeaderView.ResizeMode.ResizeToContents)
        self.__warnings_table.horizontalHeader().setSectionResizeMode(1, QHeaderView.ResizeMode.Stretch)

        for i in range(len(self.platforms)):
            self.__warnings_table.horizontalHeader().setSectionResizeMode(i + 2,
                                                                          QHeaderView.ResizeMode.ResizeToContents)

        for entry in self.__warnings:
            for header in self.header_list:
                if header not in entry.keys():
                    entry[header] = ''

        self.update_table_items(bypass_save_enable)

    def remove_table_row(self, row_index: int) -> None:
        self.warnings_table.removeRow(row_index)

        for i in range(self.warnings_table.rowCount() - 1):
            cell_widget: QPushButton = self.warnings_table.cellWidget(i, 0)

            if cell_widget is None:
                continue

            self.warnings_table.cellWidget(i, 0).disconnect()
            self.warnings_table.cellWidget(i, 0).clicked.connect(lambda: self.remove_table_row(i))

        self.warnings.remove(self.warnings[row_index])
        self.check_for_save_update()

    def update_table_items(self, bypass_save_enable=False) -> None:
        self.__warnings_table.clearContents()
        self.__warnings_table.setRowCount(len(self.warnings))

        for i in range(len(self.warnings)):
            for header in self.header_list:
                if len(header) == 0:
                    button = QPushButton("-", self)
                    button.setFixedSize(QSize(25, 25))

                    self.warnings_table.setCellWidget(i, 0, button)
                    button.clicked.connect(lambda: self.remove_table_row(i))
                    continue

                item: QTableWidgetItem = QTableWidgetItem()
                item.setText(self.warnings[i][header])

                self.warnings_table.setItem(i, self.header_list.index(header), item)

        self.insert_helper_item(bypass_save_enable)

    def insert_helper_item(self, bypass_save_enable=False) -> None:
        button = QPushButton("+", self)

        self.warnings_table.setRowCount(self.warnings_table.rowCount() + 1)
        self.warnings_table.setCellWidget(self.warnings_table.rowCount() - 1, 0, button)

        for i in range(self.warnings_table.columnCount()):
            item = self.warnings_table.item(self.warnings_table.rowCount() - 1, i)

            if item is None:
                item = QTableWidgetItem()
                self.warnings_table.setItem(self.warnings_table.rowCount() - 1, i, item)

            item.setFlags(item.flags() ^ Qt.ItemFlag.ItemIsEnabled)

        button.setFixedSize(QSize(25, 25))
        button.clicked.connect(lambda: self.insert_new_item(bypass_save_enable))

    def insert_new_item(self, bypass_save_enable=False) -> None:
        self.warning_updates_disabled = True

        self.warnings_table.removeRow(self.warnings_table.rowCount() - 1)
        self.warnings_table.setRowCount(self.warnings_table.rowCount() + 1)

        button = QPushButton("-", self)
        button.setFixedSize(QSize(25, 25))

        row: int = self.warnings_table.rowCount() - 1

        self.warnings_table.setCellWidget(row, 0, button)
        button.clicked.connect(lambda: self.remove_table_row(row))

        self.insert_helper_item()

        self.warnings.append({i: '' for i in self.header_list if i})

        self.warning_updates_disabled = False
        self.check_for_save_update()

    def close_platforms_window(self) -> None:
        self.setEnabled(True)
        self.force_disabled = False
        self.window_on_top = None

    def open_platforms_window(self) -> None:
        self.setDisabled(True)
        self.force_disabled = True
        self.window_on_top = PlatformWindow(platforms=self.platforms, parent=None)
        self.window_on_top.show()
        self.window_on_top.raise_()

        # noinspection PyUnresolvedReferences
        self.window_on_top.closed.connect(lambda: self.save_platforms_window_data(self.window_on_top.platforms))

    def update_warnings(self, row: int, column: int):
        if self.warning_updates_disabled or column == 0 or row >= len(self.warnings):
            return

        header_name = self.warnings_table.horizontalHeaderItem(column).text()
        self.warnings[row][header_name] = self.warnings_table.item(row, column).text()

        if self.__loaded_configuration is not None:
            self.configuration_save_button.setEnabled(True)

    def add_warning_fields(self) -> None:
        layout: QLayout = QVBoxLayout()

        self.layout().addItem(layout)

        header_layout: QLayout = QHBoxLayout()
        header_layout.addWidget(QLabel("""Warnings""", self))
        header_layout.addWidget(self.edit_platforms_button)
        header_layout.setAlignment(self.edit_platforms_button, Qt.AlignmentFlag.AlignRight)

        self.edit_platforms_button.clicked.connect(lambda: self.open_platforms_window())

        layout.addItem(header_layout)
        layout.addWidget(self.warnings_table)

        self.update_platform_headers()
        self.warnings_table.cellChanged.connect(lambda row, column: self.update_warnings(row, column))

    def add_generation_inputs(self) -> None:
        right_widget = QWidget(self)
        self.layout().addWidget(right_widget)

        # noinspection PyTypeChecker
        self.layout().setAlignment(right_widget, Qt.AlignmentFlag.AlignRight | Qt.AlignmentFlag.AlignBottom)

        right_widget.setLayout(QHBoxLayout())

        generate_button = QPushButton("Generate Header", right_widget)
        right_widget.layout().addWidget(generate_button)

        generate_button.clicked.connect(lambda: self.generate())

    def get_current_configuration(self) -> Union[Dict[str, Any], None]:
        if len(self.header_name_input.text()) == 0:
            QMessageBox.critical(self, "Input Data Error", "Header Name cannot be Empty!",
                                 QMessageBox.StandardButton.Ok, QMessageBox.StandardButton.Ok)
            return None

        if len(self.header_output_path_input.text()) == 0:
            QMessageBox.critical(self, "Input Data Error", "Header Output Path cannot be Empty!",
                                 QMessageBox.StandardButton.Ok, QMessageBox.StandardButton.Ok)
            return None

        if self.header_name_input.text()[self.header_name_input.text().find('.'):].lower() \
                not in ['.h', '.hh', '.hpp']:
            # noinspection PyTypeChecker

            if QMessageBox.StandardButton.Yes != QMessageBox.warning(self,
                                                                     "Header Extension Unknown", """Header extension is
            not .h, .hpp or .hh, continue?""", QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No,
                                                                     QMessageBox.StandardButton.No):
                return None

        name_violations: [int] = []

        for i in range(len(self.warnings)):
            if not self.warnings[i]['Name']:
                name_violations.append(i)

        if name_violations:
            as_string = ''
            for i in name_violations:
                as_string += '  ' + str(i + 1) + '\n'
            if as_string:
                as_string = as_string[:-1]
            QMessageBox.critical(self, "Unnamed Warning Suppression", "The items at the following rows are not named:\n"
                                 + as_string, QMessageBox.StandardButton.Ok, QMessageBox.StandardButton.Ok)

            return None

        type_violations: Dict[str, ([str], str)] = {}
        final_values: List[Dict[str, Union[str, int]]] = []

        for platform in self.platforms:
            for i in range(len(self.warnings)):
                while i >= len(final_values):
                    final_values.append({'Name': self.warnings[i]['Name']})

                if platform.warning_type.value == Platform.WarningType.INTEGER:
                    try:
                        if len(self.warnings[i][platform.platform_name]) == 0:
                            continue

                        final_values[i][platform.platform_name] = int(self.warnings[i][platform.platform_name])
                    except ValueError:
                        if platform.platform_name not in type_violations.keys():
                            type_violations[platform.platform_name] = ([], 'Integer')

                        type_violations[platform.platform_name][0].append(self.warnings[i]['Name'])

                if platform.warning_type.value == Platform.WarningType.COMMENT:
                    try:
                        if len(self.warnings[i][platform.platform_name]) == 0:
                            continue

                        final_values[i][platform.platform_name] = str(self.warnings[i][platform.platform_name])
                    except ValueError:
                        if platform.platform_name not in type_violations.keys():
                            type_violations[platform.platform_name] = ([], 'Comment')

                        type_violations[platform.platform_name][0].append(self.warnings[i]['Name'])

        if type_violations.keys():
            all_str: str = ''

            for key in type_violations.keys():
                current_str = f"{len(type_violations[key][0])} '{key}' platform violations, of type" \
                              f" '{type_violations[key][1]}':\n"

                for name in type_violations[key][0]:
                    current_str += f'  {name}\n'

                all_str += current_str + '\n'

            QMessageBox.critical(self, "Type Validation Error", "The following Warning Suppression Fields have type "
                                                                "validation errors:\n" + all_str,
                                 QMessageBox.StandardButton.Ok, QMessageBox.StandardButton.Ok)

            return None

        return self.get_current_configuration_from_values(final_values)

    def get_current_configuration_from_values(self, values: List[Dict[str, Union[str, int]]]):
        return {
            'name': self.header_name_input.text(),
            'dirpath': self.header_output_path_input.text(),
            'platforms': [{'name': name.platform_name, 'type': int(name.warning_type)} for name in self.platforms],
            'warnings': values
        }

    def generate(self):
        temp_cfg = open('_tempcfg.json', 'w')
        cfg = self.get_current_configuration()
        json.dump(cfg, temp_cfg, indent=4)
        temp_cfg.close()

        generate_header('_tempcfg.json')

        os.remove('_tempcfg.json')
        QMessageBox.information(self, "Success", "File Generated Successfully!",
                                QMessageBox.StandardButton.Ok, QMessageBox.StandardButton.Ok)

    def check_for_save_update(self) -> None:
        update = False

        if self.__loaded_configuration is not None:
            if self.header_name_input.text() != self.__loaded_configuration['name']:
                update = True
            elif self.header_output_path_input.text() != self.__loaded_configuration['dirpath']:
                update = True
            else:
                if len(self.__loaded_configuration['platforms']) != len(self.platforms):
                    update = True

                if not update:
                    if len(self.warnings) != len(self.__loaded_configuration['warnings']):
                        update = True

                if not update:
                    for i in self.__loaded_configuration['platforms']:
                        if Platform(i['type'], i['name']) in self.platforms:
                            update = True

        self.configuration_save_button.setEnabled(update)


def main(argv: List[str]) -> None:
    application: QApplication = QApplication(argv)

    window: GeneratorWindow = GeneratorWindow()
    window.show()

    application.exec()


if __name__ == '__main__':
    main(argv=program_arguments)
