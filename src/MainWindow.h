#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QMenuBar>
#include <QMenu>

#include "File/STLFile.h"

class OpenGLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

private:
	void createAction();  // create actions
	void createMenu();  // create menus
	void createToolbars();
	void addActiontosToToolBar();  // add actions to bar
	void addActionsToMenu();  // add actions to menu
	void addMenusToMenuBar();  // add menu to bar

private:
	// toolbars
	QToolBar* m_pMainToolBar;
	QToolBar* m_pViewToolBar;

	// file
	QMenu* m_pFileMenu{ nullptr }; // file menue
	QAction* m_pOpenFileAction{ nullptr };  // open file action
	QAction* m_pSaveFileAction{ nullptr };
	QAction* m_pSAveAsFileAction{ nullptr };
	QAction* m_pSetWorkSpaceAction{ nullptr };
	QAction* m_pImputApdlModelFileAction{ nullptr };
	QAction* m_pImputFeamModelFileAction{ nullptr };
	QAction* m_pImputTestModelFileAction{ nullptr };
	QAction* m_pOutputWordReportAction{ nullptr };

	// edit
	QMenu* m_pEditMenu{ nullptr }; // edit menu
	QAction* m_pCopyDataAction{ nullptr };
	QAction* m_pCutDataAction{ nullptr };
	QAction* m_pPastDataAction{ nullptr };
	QAction* m_pDeleteDataAction{ nullptr };
	QAction* m_pSelectAllAction{ nullptr };
	QAction* m_pUnselectAction{ nullptr };

	// view
	QMenu* m_pViewMenu{ nullptr }; // view menu
	QAction* m_pShowDataTreeAction{ nullptr };
	QAction* m_pShowCommonAction{ nullptr };
	QAction* m_pShowMeshAction{ nullptr };
	QAction* m_pTransparencyAction{ nullptr };
	QAction* m_pShowPointAction{ nullptr };
	QAction* m_pShowPointNameAction{ nullptr };
	QAction* m_pShowDOFAction{ nullptr };
	QAction* m_pLeftViewAction{ nullptr };
	QAction* m_pRightViewAction{ nullptr };
	QAction* m_pButtonViewAction{ nullptr };
	QAction* m_pTopViewAction{ nullptr };
	QAction* m_pFrondViewAction{ nullptr };
	QAction* m_pBackViewAction{ nullptr };
	QAction* m_pIOSViewAction{ nullptr };
	QAction* m_pSelectFromAction{ nullptr };
	QAction* m_pSetToSelfAction{ nullptr };

	// process
	QMenu* m_pProcessMenu{ nullptr };  // process menu
	QAction* m_pStaticsAnalysisAction{ nullptr };
	QAction* m_pMeshConvergenceAction{ nullptr };
	QAction* m_pCorrelationAnalysisAction{ nullptr };

	QMenu* m_pProgramSetMenu{ nullptr };
	QAction* m_pSetProgramAction{ nullptr };
	QAction* m_pSetTargetAction{ nullptr };
	QAction* m_pAnalysisProgramAction{ nullptr };
	QAction* m_pModelUpdatingAction{ nullptr };

	// tools
	QMenu* m_pToolMenu{ nullptr };
	QAction* m_pScreenShortAction{ nullptr };

	// windows
	QMenu* m_pWindMenu{ nullptr };
	QAction* m_pShowWindowsAsTabsAction{ nullptr };
	QAction* m_pShowWindowsAsVerticalAction{ nullptr };
	QAction* m_pShowWindowsAsHorizontalAction{ nullptr };
	QAction* m_pShowWindowsAsStackAcion{ nullptr };

	// setup
	QMenu* m_pSetUpMenu{ nullptr };
	QAction* m_pSetSolverPathAction{ nullptr };
	QAction* m_pSetSeverAction{ nullptr };
	QAction* m_pSetBaseAction{ nullptr };
	QAction* m_pSetShortcutAction{ nullptr };

	// about
	QMenu* m_pAboutMenu{ nullptr };

	// second floor menu
	QMenu* m_pHelpManualMenu{ nullptr };

	// second floot actions
	QAction* m_pInstallManualAction{ nullptr };
	QAction* m_pTrainManualAction{ nullptr };
	QAction* m_pTheoryAction{ nullptr };
	QAction* m_pUserAction{ nullptr };

	// top actions
	QAction* m_pLicenseAction{ nullptr };
	QAction* m_pLearningOnlineAction{ nullptr };
	QAction* m_pConnectAction{ nullptr };
	QAction* m_pAboutAction{ nullptr };
	QAction* m_pExitAction{ nullptr };

	OpenGLWidget* m_popenglWidget{ nullptr };
};
#endif // MAINWINDOW_H
