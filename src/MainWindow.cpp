#include "mainwindow.h"

#include "OpenGLWidget/GLWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createAction();
    createMenu();
    createToolbars();
    addActiontosToToolBar();
    addActionsToMenu();
    addMenusToMenuBar();
    m_popenglWidget = new GLWidget(this);
    setCentralWidget(m_popenglWidget);
}

void MainWindow::createAction()
{
    // all the files
    m_pOpenFileAction = new QAction(this);
    m_pOpenFileAction->setText(QString::fromLocal8Bit("Open"));
    m_pOpenFileAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pOpenFileAction->setIcon(QIcon(":/menue/actions/resource/png/action/OpenFiles.png")); 
    connect(m_pOpenFileAction, SIGNAL(triggered(bool)), this, SLOT(openFile()));

    // save the files
    m_pSaveFileAction = new QAction(this);
    m_pSaveFileAction->setText(QString::fromLocal8Bit("Save"));
    m_pSaveFileAction->setShortcut(QKeySequence("Ctrl+S"));
    m_pSaveFileAction->setIcon(QIcon(":/menue/actions/resource/png/action/save.png"));
    connect(m_pSaveFileAction, SIGNAL(triggered(bool)), this, SLOT(SaveFile()));

    // save as the files
    m_pSAveAsFileAction = new QAction(this);
    m_pSAveAsFileAction->setText(QString::fromLocal8Bit("Save as..."));
    m_pSAveAsFileAction->setShortcut(QKeySequence("Ctrl+Shift+S"));
    m_pSAveAsFileAction->setIcon(QIcon(":/menue/actions/resource/png/action/saveAs.PNG"));
    connect(m_pSAveAsFileAction, SIGNAL(triggered(bool)), this, SLOT(SaveAsFile()));

    // set the workspace
    m_pSetWorkSpaceAction = new QAction(this);
    m_pSetWorkSpaceAction->setText(QString::fromLocal8Bit("WorkSpace"));
    m_pSetWorkSpaceAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pSetWorkSpaceAction->setIcon(QIcon(":/menue/actions/resource/png/action/setPath.png"));
    connect(m_pSetWorkSpaceAction, SIGNAL(triggered(bool)), this, SLOT(SetWorkSpace()));

    // import the apdl
    m_pImputApdlModelFileAction = new QAction(this);
    m_pImputApdlModelFileAction->setText(QString::fromLocal8Bit("ImportAPDL"));
    m_pImputApdlModelFileAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pImputApdlModelFileAction->setIcon(QIcon(":/menue/actions/resource/png/action/imputAPDL.png"));
    connect(m_pImputApdlModelFileAction, SIGNAL(triggered(bool)), this, SLOT(ImputApdlModelFile()));

    // import the simulate
    m_pImputFeamModelFileAction = new QAction(this);
    m_pImputFeamModelFileAction->setText(QString::fromLocal8Bit("ImportSimulate"));
    m_pImputFeamModelFileAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pImputFeamModelFileAction->setIcon(QIcon(":/menue/actions/resource/png/action/imputSimulate.png"));
    connect(m_pImputFeamModelFileAction, SIGNAL(triggered(bool)), this, SLOT(ImputFeamModelFile()));

    // import the test
    m_pImputTestModelFileAction = new QAction(this);
    m_pImputTestModelFileAction->setText(QString::fromLocal8Bit("ImportTest"));
    m_pImputTestModelFileAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pImputTestModelFileAction->setIcon(QIcon(":/menue/actions/resource/png/action/imputTest.png"));
    connect(m_pImputTestModelFileAction, SIGNAL(triggered(bool)), this, SLOT(ImputTestModelFile()));

    // output the word
    m_pOutputWordReportAction = new QAction(this);
    m_pOutputWordReportAction->setText(QString::fromLocal8Bit("Output Word"));
    m_pOutputWordReportAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pOutputWordReportAction->setIcon(QIcon(":/menue/actions/resource/png/action/writeWord.png"));
    connect(m_pOutputWordReportAction, SIGNAL(triggered(bool)), this, SLOT(OutputWordReport()));

    // copy
    m_pCopyDataAction = new QAction(this);
    m_pCopyDataAction->setText(QString::fromLocal8Bit("Copy"));
    m_pCopyDataAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pCopyDataAction->setIcon(QIcon(":/menue/actions/resource/png/action/Copy.png"));
    connect(m_pCopyDataAction, SIGNAL(triggered(bool)), this, SLOT(CopyData()));

    // cut
    m_pCutDataAction = new QAction(this);
    m_pCutDataAction->setText(QString::fromLocal8Bit("Cut"));
    m_pCutDataAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pCutDataAction->setIcon(QIcon(":/menue/actions/resource/png/action/Cut.png"));
    connect(m_pCutDataAction, SIGNAL(triggered(bool)), this, SLOT(CutData()));

    // past
    m_pPastDataAction = new QAction(this);
    m_pPastDataAction->setText(QString::fromLocal8Bit("Past"));
    m_pPastDataAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pPastDataAction->setIcon(QIcon(":/menue/actions/resource/png/action/Paste.png"));
    connect(m_pPastDataAction, SIGNAL(triggered(bool)), this, SLOT(PastData()));

    // delete
    m_pDeleteDataAction = new QAction(this);
    m_pDeleteDataAction->setText(QString::fromLocal8Bit("Delete"));
    m_pDeleteDataAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pDeleteDataAction->setIcon(QIcon(":/menue/actions/resource/png/action/Delete.png"));
    connect(m_pDeleteDataAction, SIGNAL(triggered(bool)), this, SLOT(DeleteData()));

    // select all
    m_pSelectAllAction = new QAction(this);
    m_pSelectAllAction->setText(QString::fromLocal8Bit("Select All"));
    m_pSelectAllAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pSelectAllAction->setIcon(QIcon(":/menue/actions/resource/png/action/SelectAll.png"));
    connect(m_pSelectAllAction, SIGNAL(triggered(bool)), this, SLOT(SelectAll()));

    // unselect
    m_pUnselectAction = new QAction(this);
    m_pUnselectAction->setText(QString::fromLocal8Bit("Unselect"));
    m_pUnselectAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pUnselectAction->setIcon(QIcon(""));
    connect(m_pUnselectAction, SIGNAL(triggered(bool)), this, SLOT(Unselect()));

    // all the views
    m_pShowMeshAction = new QAction(this);
    m_pShowMeshAction->setText(QString::fromLocal8Bit("ShowMesh"));
    m_pShowMeshAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pShowMeshAction->setIcon(QIcon(":/menue/actions/resource/png/action/mesh.png"));
    connect(m_pShowMeshAction, SIGNAL(triggered(bool)), this, SLOT(ShowMesh()));

    // tranparency
    m_pTransparencyAction = new QAction(this);
    m_pTransparencyAction->setText(QString::fromLocal8Bit("Tranporent"));
    m_pTransparencyAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pTransparencyAction->setIcon(QIcon(":/menue/actions/resource/png/action/Transparant.png"));
    connect(m_pTransparencyAction, SIGNAL(triggered(bool)), this, SLOT(Transparency()));

    // show point
    m_pShowPointAction = new QAction(this);
    m_pShowPointAction->setText(QString::fromLocal8Bit("ShowPoint"));
    m_pShowPointAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pShowPointAction->setIcon(QIcon(":/menue/actions/resource/png/action/ShowPoint.png"));
    connect(m_pShowPointAction, SIGNAL(triggered(bool)), this, SLOT(ShowPoint()));

    m_pShowPointNameAction = new QAction(this);
    m_pShowPointNameAction->setText(QString::fromLocal8Bit("ShowPointName"));
    m_pShowPointNameAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pShowPointNameAction->setIcon(QIcon(":/menue/actions/resource/png/action/pointName.png"));
    connect(m_pShowPointNameAction, SIGNAL(triggered(bool)), this, SLOT(ShowPointName()));

    m_pShowDOFAction = new QAction(this);
    m_pShowDOFAction->setText(QString::fromLocal8Bit("DOF"));
    m_pShowDOFAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pShowDOFAction->setIcon(QIcon(":/menue/actions/resource/png/action/DOF.png"));
    connect(m_pShowDOFAction, SIGNAL(triggered(bool)), this, SLOT(ShowDOF()));

    m_pLeftViewAction = new QAction(this);
    m_pLeftViewAction->setText(QString::fromLocal8Bit("Left"));
    m_pLeftViewAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pLeftViewAction->setIcon(QIcon(":/menue/actions/resource/png/action/Left.png"));
    connect(m_pLeftViewAction, SIGNAL(triggered(bool)), this, SLOT(LeftView()));

    m_pRightViewAction = new QAction(this);
    m_pRightViewAction->setText(QString::fromLocal8Bit("Right"));
    m_pRightViewAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pRightViewAction->setIcon(QIcon(":/menue/actions/resource/png/action/Right.png"));
    connect(m_pRightViewAction, SIGNAL(triggered(bool)), this, SLOT(RightView()));

    m_pButtonViewAction = new QAction(this);
    m_pButtonViewAction->setText(QString::fromLocal8Bit("Down"));
    m_pButtonViewAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pButtonViewAction->setIcon(QIcon(":/menue/actions/resource/png/action/down.png"));
    connect(m_pButtonViewAction, SIGNAL(triggered(bool)), this, SLOT(ButtonView()));

    m_pTopViewAction = new QAction(this);
    m_pTopViewAction->setText(QString::fromLocal8Bit("Up"));
    m_pTopViewAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pTopViewAction->setIcon(QIcon(":/menue/actions/resource/png/action/up.png"));
    connect(m_pTopViewAction, SIGNAL(triggered(bool)), this, SLOT(TopView()));

    m_pFrondViewAction = new QAction(this);
    m_pFrondViewAction->setText(QString::fromLocal8Bit("Front"));
    m_pFrondViewAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pFrondViewAction->setIcon(QIcon(":/menue/actions/resource/png/action/Frond.png"));
    connect(m_pFrondViewAction, SIGNAL(triggered(bool)), this, SLOT(FrondView()));

    m_pBackViewAction = new QAction(this);
    m_pBackViewAction->setText(QString::fromLocal8Bit("Back"));
    m_pBackViewAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pBackViewAction->setIcon(QIcon(":/menue/actions/resource/png/action/back.png"));
    connect(m_pBackViewAction, SIGNAL(triggered(bool)), this, SLOT(BackView()));

    m_pIOSViewAction = new QAction(this);
    m_pIOSViewAction->setText(QString::fromLocal8Bit("IOS"));
    m_pIOSViewAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pIOSViewAction->setIcon(QIcon(":/menue/actions/resource/png/action/ios.png"));
    connect(m_pIOSViewAction, SIGNAL(triggered(bool)), this, SLOT(BackView()));

    m_pSelectFromAction = new QAction(this);
    m_pSelectFromAction->setText(QString::fromLocal8Bit("Fram"));
    m_pSelectFromAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pSelectFromAction->setIcon(QIcon(":/menue/actions/resource/png/action/SelectForm.png"));
    connect(m_pSelectFromAction, SIGNAL(triggered(bool)), this, SLOT(BackView()));

    m_pSetToSelfAction = new QAction(this);
    m_pSetToSelfAction->setText(QString::fromLocal8Bit("Self"));
    m_pSetToSelfAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pSetToSelfAction->setIcon(QIcon(":/menue/actions/resource/png/action/atuoChange.png"));
    connect(m_pSetToSelfAction, SIGNAL(triggered(bool)), this, SLOT(BackView()));

    // all the process
    m_pStaticsAnalysisAction = new QAction(this);
    m_pStaticsAnalysisAction->setText(QString::fromLocal8Bit("Analysis"));
    m_pStaticsAnalysisAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pStaticsAnalysisAction->setIcon(QIcon(":/menue/actions/resource/png/action/AnalysisFEM.png"));
    connect(m_pStaticsAnalysisAction, SIGNAL(triggered(bool)), this, SLOT(StaticsAnalysis()));

    m_pMeshConvergenceAction = new QAction(this);
    m_pMeshConvergenceAction->setText(QString::fromLocal8Bit("Grid Convergence"));
    m_pMeshConvergenceAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pMeshConvergenceAction->setIcon(QIcon(""));
    connect(m_pMeshConvergenceAction, SIGNAL(triggered(bool)), this, SLOT(MeshConvergence()));

    m_pCorrelationAnalysisAction = new QAction(this);
    m_pCorrelationAnalysisAction->setText(QString::fromLocal8Bit("Dependency"));
    m_pCorrelationAnalysisAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pCorrelationAnalysisAction->setIcon(QIcon(""));
    connect(m_pCorrelationAnalysisAction, SIGNAL(triggered(bool)), this, SLOT(CorrelationAnalysis()));

    m_pSetProgramAction = new QAction(this);
    m_pSetProgramAction->setText(QString::fromLocal8Bit("Parameter Setting"));
    m_pSetProgramAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pSetProgramAction->setIcon(QIcon(":/menue/actions/resource/png/action/ModifyParameter.png"));
    connect(m_pSetProgramAction, SIGNAL(triggered(bool)), this, SLOT(SetProgram()));

    m_pSetTargetAction = new QAction(this);
    m_pSetTargetAction->setText(QString::fromLocal8Bit("Fixed Target"));
    m_pSetTargetAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pSetTargetAction->setIcon(QIcon(":/menue/actions/resource/png/action/ModifyTarget.png"));
    connect(m_pSetTargetAction, SIGNAL(triggered(bool)), this, SLOT(SetTarget()));

    m_pAnalysisProgramAction = new QAction(this);
    m_pAnalysisProgramAction->setText(QString::fromLocal8Bit("Sensitivity Analysis"));
    m_pAnalysisProgramAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pAnalysisProgramAction->setIcon(QIcon(":/menue/actions/resource/png/action/AnalysisSensitivity.png"));
    connect(m_pAnalysisProgramAction, SIGNAL(triggered(bool)), this, SLOT(AnalysisProgram()));

    m_pModelUpdatingAction = new QAction(this);
    m_pModelUpdatingAction->setText(QString::fromLocal8Bit("Updatting"));
    m_pModelUpdatingAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pModelUpdatingAction->setIcon(QIcon(":/menue/actions/resource/png/action/updateModel.png"));
    connect(m_pModelUpdatingAction, SIGNAL(triggered(bool)), this, SLOT(ModelUpdating()));

    // all the tools
    m_pScreenShortAction = new QAction(this);
    m_pScreenShortAction->setText(QString::fromLocal8Bit("Screen Shot"));
    m_pScreenShortAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pScreenShortAction->setIcon(QIcon(""));
    connect(m_pScreenShortAction, SIGNAL(triggered(bool)), this, SLOT(ScreenShort()));

    // all the windows
    m_pShowDataTreeAction = new QAction(this);
    m_pShowDataTreeAction->setText(QString::fromLocal8Bit("Data Tree"));
    m_pShowDataTreeAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pShowDataTreeAction->setIcon(QIcon(":/menue/actions/resource/png/action/LeftWindow.png"));
    connect(m_pShowDataTreeAction, SIGNAL(triggered(bool)), this, SLOT(ShowDataTree()));

    m_pShowCommonAction = new QAction(this);
    m_pShowCommonAction->setText(QString::fromLocal8Bit("Common"));
    m_pShowCommonAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pShowCommonAction->setIcon(QIcon(":/menue/actions/resource/png/action/downWindow.png"));
    connect(m_pShowCommonAction, SIGNAL(triggered(bool)), this, SLOT(ShowCommon()));

    m_pShowWindowsAsTabsAction = new QAction(this);
    m_pShowWindowsAsTabsAction->setText(QString::fromLocal8Bit("TabList"));
    m_pShowWindowsAsTabsAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pShowWindowsAsTabsAction->setIcon(QIcon(":/menue/actions/resource/png/action/tablist.png"));
    connect(m_pShowWindowsAsTabsAction, SIGNAL(triggered(bool)), this, SLOT(ShowWindowsAsTabs()));

    m_pShowWindowsAsVerticalAction = new QAction(this);
    m_pShowWindowsAsVerticalAction->setText(QString::fromLocal8Bit("Horizontal"));
    m_pShowWindowsAsVerticalAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pShowWindowsAsVerticalAction->setIcon(QIcon(":/menue/actions/resource/png/action/upDown.png"));
    connect(m_pShowWindowsAsVerticalAction, SIGNAL(triggered(bool)), this, SLOT(ShowWindowsAsVertical()));

    m_pShowWindowsAsHorizontalAction = new QAction(this);
    m_pShowWindowsAsHorizontalAction->setText(QString::fromLocal8Bit("Vertical"));
    m_pShowWindowsAsHorizontalAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pShowWindowsAsHorizontalAction->setIcon(QIcon(":/menue/actions/resource/png/action/LeftRight.png"));
    connect(m_pShowWindowsAsHorizontalAction, SIGNAL(triggered(bool)), this, SLOT(ShowWindowsAsHorizontal()));

    m_pShowWindowsAsStackAcion = new QAction(this);
    m_pShowWindowsAsStackAcion->setText(QString::fromLocal8Bit("Stack"));
    m_pShowWindowsAsStackAcion->setShortcut(QKeySequence("Ctrl+O"));
    m_pShowWindowsAsStackAcion->setIcon(QIcon(":/menue/actions/resource/png/action/StackWindow.png"));
    connect(m_pShowWindowsAsStackAcion, SIGNAL(triggered(bool)), this, SLOT(ShowWindowsAsStack()));

    // all the setting
    m_pSetSolverPathAction = new QAction(this);
    m_pSetSolverPathAction->setText(QString::fromLocal8Bit("Solver"));
    m_pSetSolverPathAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pSetSolverPathAction->setIcon(QIcon(":/menue/actions/resource/png/action/ThirdSoftWarePath.png"));
    connect(m_pSetSolverPathAction, SIGNAL(triggered(bool)), this, SLOT(SetSolverPath()));

    m_pSetSeverAction = new QAction(this);
    m_pSetSeverAction->setText(QString::fromLocal8Bit("Server"));
    m_pSetSeverAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pSetSeverAction->setIcon(QIcon(":/menue/actions/resource/png/action/ServerConfiguration.png"));
    connect(m_pSetSeverAction, SIGNAL(triggered(bool)), this, SLOT(SetSever()));

    m_pSetBaseAction = new QAction(this);
    m_pSetBaseAction->setText(QString::fromLocal8Bit("BaseSet"));
    m_pSetBaseAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pSetBaseAction->setIcon(QIcon(":/menue/actions/resource/png/action/Setting.png"));
    connect(m_pSetBaseAction, SIGNAL(triggered(bool)), this, SLOT(SetBase()));

    m_pSetShortcutAction = new QAction(this);
    m_pSetShortcutAction->setText(QString::fromLocal8Bit("ShortCut"));
    m_pSetShortcutAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pSetShortcutAction->setIcon(QIcon(":/menue/actions/resource/png/action/ShortCut.png"));
    connect(m_pSetShortcutAction, SIGNAL(triggered(bool)), this, SLOT(SetShortCutAction()));

    // all the help manual
    m_pInstallManualAction = new QAction(this);
    m_pInstallManualAction->setText(QString::fromLocal8Bit("Install Manual"));
    m_pInstallManualAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pInstallManualAction->setIcon(QIcon(":/menue/actions/resource/png/action/InstallDoc.png"));
    connect(m_pInstallManualAction, SIGNAL(triggered(bool)), this, SLOT(InstallManual()));

    m_pTrainManualAction = new QAction(this);
    m_pTrainManualAction->setText(QString::fromLocal8Bit("Training Manual"));
    m_pTrainManualAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pTrainManualAction->setIcon(QIcon(":/menue/actions/resource/png/action/BasicTrainDoc.png"));
    connect(m_pTrainManualAction, SIGNAL(triggered(bool)), this, SLOT(TrainManual()));

    m_pTheoryAction = new QAction(this);
    m_pTheoryAction->setText(QString::fromLocal8Bit("Theory Manual"));
    m_pTheoryAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pTheoryAction->setIcon(QIcon(":/menue/actions/resource/png/action/TheoryDoc.png"));
    connect(m_pTheoryAction, SIGNAL(triggered(bool)), this, SLOT(TheoryManual()));

    m_pUserAction = new QAction(this);
    m_pUserAction->setText(QString::fromLocal8Bit("User Manual"));
    m_pUserAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pUserAction->setIcon(QIcon(":/menue/actions/resource/png/action/UserDoc.png"));
    connect(m_pUserAction, SIGNAL(triggered(bool)), this, SLOT(UserManual()));

    m_pLicenseAction = new QAction(this);
    m_pLicenseAction->setText(QString::fromLocal8Bit("License"));
    m_pLicenseAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pLicenseAction->setIcon(QIcon(":/menue/actions/resource/png/action/LicenseInfo.png"));
    connect(m_pLicenseAction, SIGNAL(triggered(bool)), this, SLOT(LicenseInformation()));

    m_pLearningOnlineAction = new QAction(this);
    m_pLearningOnlineAction->setText(QString::fromLocal8Bit("Learnning On Line"));
    m_pLearningOnlineAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pLearningOnlineAction->setIcon(QIcon(":/menue/actions/resource/png/action/OnlineLearning.png"));
    connect(m_pLearningOnlineAction, SIGNAL(triggered(bool)), this, SLOT(LearningOnline()));

    m_pConnectAction = new QAction(this);
    m_pConnectAction->setText(QString::fromLocal8Bit("Connect Us"));
    m_pConnectAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pConnectAction->setIcon(QIcon(":/menue/actions/resource/png/action/ContactUs.png"));
    connect(m_pConnectAction, SIGNAL(triggered(bool)), this, SLOT(ConnectionUs()));

    m_pAboutAction = new QAction(this);
    m_pAboutAction->setText(QString::fromLocal8Bit("About SimVVer"));
    m_pAboutAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pAboutAction->setIcon(QIcon(":/menue/actions/resource/png/action/AboutSimVVer.png"));
    connect(m_pAboutAction, SIGNAL(triggered(bool)), this, SLOT(AboutUs()));

    m_pExitAction = new QAction(this);
    m_pExitAction->setText(QString::fromLocal8Bit("Close"));
    m_pExitAction->setShortcut(QKeySequence(Qt::Key_Exit));
    m_pExitAction->setIcon(QIcon(":/menue/actions/resource/png/action/Quit.png"));
    connect(m_pExitAction, SIGNAL(triggered(bool)), this, SLOT(close()));
}

void MainWindow::createMenu()
{
    m_pFileMenu = new QMenu(this);
    m_pFileMenu->setTitle(QString::fromLocal8Bit("File"));

    m_pEditMenu = new QMenu(this);
    m_pEditMenu->setTitle(QString::fromLocal8Bit("Edit"));

    m_pViewMenu = new QMenu(this);
    m_pViewMenu->setTitle(QString::fromLocal8Bit("View"));

    m_pProcessMenu = new QMenu(this);
    m_pProcessMenu->setTitle(QString::fromLocal8Bit("Process"));

    m_pProgramSetMenu = new QMenu(m_pProcessMenu);
    m_pProgramSetMenu->setTitle(QString::fromLocal8Bit("ProgramSet"));

    m_pToolMenu = new QMenu(this);
    m_pToolMenu->setTitle(QString::fromLocal8Bit("Tools"));

    m_pWindMenu = new QMenu(this);
    m_pWindMenu->setTitle(QString::fromLocal8Bit("Windows"));

    m_pSetUpMenu = new QMenu(this);
    m_pSetUpMenu->setTitle(QString::fromLocal8Bit("Setting"));

    m_pAboutMenu = new QMenu(this);
    m_pAboutMenu->setTitle(QString::fromLocal8Bit("Aboue"));

    m_pHelpManualMenu = new QMenu(m_pAboutMenu);
    m_pHelpManualMenu->setTitle(QString::fromLocal8Bit("Help"));
}

void MainWindow::createToolbars()
{
    m_pMainToolBar = new QToolBar(this);
    m_pViewToolBar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, m_pMainToolBar);
    addToolBar(Qt::RightToolBarArea, m_pViewToolBar);
}

void MainWindow::addActionsToMenu()
{
    // all the file
    m_pFileMenu->addAction(m_pOpenFileAction);
}

void MainWindow::addMenusToMenuBar()
{
    menuBar()->addMenu(m_pFileMenu);
    menuBar()->addMenu(m_pEditMenu);
    menuBar()->addMenu(m_pViewMenu);
    menuBar()->addMenu(m_pProcessMenu);
    menuBar()->addMenu(m_pProgramSetMenu);
    menuBar()->addMenu(m_pToolMenu);
    menuBar()->addMenu(m_pWindMenu);
    menuBar()->addMenu(m_pSetUpMenu);
    menuBar()->addMenu(m_pAboutMenu);
    menuBar()->addMenu(m_pHelpManualMenu);
}

void MainWindow::addActiontosToToolBar()
{
    m_pMainToolBar->setMovable(false);
    m_pMainToolBar->addAction(m_pOpenFileAction);
    m_pMainToolBar->addAction(m_pSaveFileAction);
    m_pMainToolBar->addAction(m_pSAveAsFileAction);
    m_pMainToolBar->addAction(m_pImputApdlModelFileAction);
    m_pMainToolBar->addAction(m_pImputFeamModelFileAction);
    m_pMainToolBar->addAction(m_pImputTestModelFileAction);
    m_pMainToolBar->addSeparator();
    m_pMainToolBar->addAction(m_pSelectFromAction);
    m_pMainToolBar->addAction(m_pSetToSelfAction);
    m_pMainToolBar->addSeparator();
    m_pMainToolBar->addAction(m_pShowDataTreeAction);
    m_pMainToolBar->addAction(m_pShowCommonAction);
    m_pMainToolBar->addSeparator();
    m_pMainToolBar->addAction(m_pShowWindowsAsTabsAction);
    m_pMainToolBar->addAction(m_pShowWindowsAsVerticalAction);
    m_pMainToolBar->addAction(m_pShowWindowsAsHorizontalAction);
    m_pMainToolBar->addAction(m_pShowWindowsAsStackAcion);
    m_pMainToolBar->addSeparator();
    m_pMainToolBar->addAction(m_pAboutAction);
    m_pMainToolBar->addAction(m_pExitAction);

    m_pViewToolBar->addAction(m_pLeftViewAction);
    m_pViewToolBar->addAction(m_pRightViewAction);
    m_pViewToolBar->addAction(m_pButtonViewAction);
    m_pViewToolBar->addAction(m_pTopViewAction);
    m_pViewToolBar->addAction(m_pFrondViewAction);
    m_pViewToolBar->addAction(m_pBackViewAction);
    m_pViewToolBar->addAction(m_pIOSViewAction);
    m_pViewToolBar->addSeparator();
    m_pViewToolBar->addAction(m_pShowMeshAction);
    m_pViewToolBar->addAction(m_pTransparencyAction);
    m_pViewToolBar->addAction(m_pShowPointAction);
    m_pViewToolBar->addAction(m_pShowPointNameAction);
}

MainWindow::~MainWindow()
{
}
