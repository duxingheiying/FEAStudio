#include "MainWindow.h"

#include <QAction>
#include <QFileInfo>
#include <QFileDialog>
#include <QMdiArea>

#include "GraphicMdiSubWin.h"
#include "TableMdiSubWin.h"
#include "CurveMdiSubWin.h"

#include "MessageDockWidget.h"
#include "TreeDockWidget.h"
#include "PropertyDockWidget.h"

#include "GLWidget.h"
#include "fileanalysis/BDFAnalysis.h"
#include "CDBAnalysis.h"
#include "UFFAnalysis.h"
#include "UNVAnalysis.h"
#include "TxtAnalysis.h"
#include "STLAnalysis.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // change window tile
    setWindowTitle(tr("EngieStudio"));

    m_pCenterMainWindow = new QMainWindow(this);
    m_pCenterMainWindow->setWindowFlags(Qt::Widget);
    m_MdiAreaWidget = new QMdiArea(m_pCenterMainWindow);
    m_MdiAreaWidget->setAttribute(Qt::WA_TranslucentBackground, true);
    m_pCenterMainWindow->setCentralWidget(m_MdiAreaWidget);
    m_pCenterMainWindow->showNormal();
    setCentralWidget(m_pCenterMainWindow);

    m_pTreeDockWidget = new TreeDockWidget(this);
    addDockWidget(Qt::LeftDockWidgetArea, m_pTreeDockWidget);

    m_pPropertyDockWidget = new PropertyDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea, m_pPropertyDockWidget);

    m_pMSDockWidget = new MessageDockWidget(m_pCenterMainWindow);
//    splitDockWidget(m_pTreeDockWidget,m_pMSDockWidget,Qt::Horizontal);
//    splitDockWidget(m_pMSDockWidget,m_pPropertyDockWidget,Qt::Vertical);
    m_pCenterMainWindow->addDockWidget(Qt::BottomDockWidgetArea, m_pMSDockWidget);

    // create new class for read files
    m_pBdfFile = new BDFFile(nullptr);
    m_pCbdFile = new CBDFile(nullptr);
    m_pTxtFile = new TxtFile(nullptr);
    m_pSTLFile = new STLFile(nullptr);

    connect(m_pBdfFile, &AnalysisFile::showMessage, m_pMSDockWidget, &MessageDockWidget::outMessage);

    // create new thread for read all the files
    m_pReadBDFThread = new QThread(nullptr);
    m_pBdfFile->moveToThread(m_pReadBDFThread);

    m_pReadCBDThread = new QThread(nullptr);
    m_pCbdFile->moveToThread(m_pReadCBDThread);

    m_pReadTxtThread = new QThread(nullptr);
    m_pTxtFile->moveToThread(m_pReadTxtThread);

    m_pReadSTLThread = new QThread(nullptr);
    m_pSTLFile->moveToThread(m_pReadSTLThread);

    connect(this, &MainWindow::startReadBDF, m_pBdfFile, &AnalysisFile::ReadFile);
    connect(m_pBdfFile, &AnalysisFile::ReadFileFinished, this, &MainWindow::updateBDFToOpenGL);
    connect(m_pReadBDFThread, &QThread::finished, m_pBdfFile, &QObject::deleteLater);

    connect(this, &MainWindow::startReadCDB, m_pCbdFile, &AnalysisFile::ReadFile);

    connect(this, &MainWindow::startReadTXT, m_pTxtFile, &AnalysisFile::ReadFile);
    connect(m_pTxtFile, &AnalysisFile::ReadFileFinished, this, &MainWindow::updateTxtToOpenGL);
    connect(m_pReadTxtThread, &QThread::finished, m_pTxtFile, &QObject::deleteLater);

    connect(this, &MainWindow::startReadSTL, m_pSTLFile, &AnalysisFile::ReadFile);
    connect(m_pSTLFile, &AnalysisFile::ReadFileFinished, this, &MainWindow::updateSTLToOpenGL);

    // start all the thread
    m_pReadBDFThread->start();
    m_pReadCBDThread->start();
    m_pReadTxtThread->start();
    m_pReadSTLThread->start();

    createMenuBar();
    createAction();
    createMenu();
    createToolbars();
    addActiontosToToolBar();
    addActionsToMenu();
    addMenusToMenuBar();

    CreateNewCurveWindow();
    CreateNewTableWindow();
    CreateNewGraphicWindow();

    showMaximized(); // show as max window
}


void MainWindow::createMenuBar()
{
    m_pMenuBar = new QMenuBar(this);
    setMenuBar(m_pMenuBar);
}

// :/Icon/Actions/AboutSimVVer.png

void MainWindow::createAction()
{
    // all the files
    m_pOpenFileAction = new QAction(this);
    m_pOpenFileAction->setText(QString::fromLocal8Bit("Open"));
    m_pOpenFileAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pOpenFileAction->setIcon(QIcon(":/Icon/Actions/OpenFiles.png"));
    connect(m_pOpenFileAction, SIGNAL(triggered(bool)), this, SLOT(openFile()));

    // save the files
    m_pSaveFileAction = new QAction(this);
    m_pSaveFileAction->setText(QString::fromLocal8Bit("Save"));
    m_pSaveFileAction->setShortcut(QKeySequence("Ctrl+S"));
    m_pSaveFileAction->setIcon(QIcon(":/Icon/Actions/save.png"));
    connect(m_pSaveFileAction, SIGNAL(triggered(bool)), this, SLOT(SaveFile()));

    // save as the files
    m_pSAveAsFileAction = new QAction(this);
    m_pSAveAsFileAction->setText(QString::fromLocal8Bit("Save as..."));
    m_pSAveAsFileAction->setShortcut(QKeySequence("Ctrl+Shift+S"));
    m_pSAveAsFileAction->setIcon(QIcon(":/Icon/Actions/saveAs.PNG"));
    connect(m_pSAveAsFileAction, SIGNAL(triggered(bool)), this, SLOT(SaveAsFile()));

    // set the workspace
    m_pSetWorkSpaceAction = new QAction(this);
    m_pSetWorkSpaceAction->setText(QString::fromLocal8Bit("WorkSpace"));
    m_pSetWorkSpaceAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pSetWorkSpaceAction->setIcon(QIcon(":/Icon/Actions/setPath.png"));
    connect(m_pSetWorkSpaceAction, SIGNAL(triggered(bool)), this, SLOT(SetWorkSpace()));

    // import the apdl
    m_pImputApdlModelFileAction = new QAction(this);
    m_pImputApdlModelFileAction->setText(QString::fromLocal8Bit("ImportAPDL"));
    m_pImputApdlModelFileAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pImputApdlModelFileAction->setIcon(QIcon(":/Icon/Actions/imputAPDL.png"));
    connect(m_pImputApdlModelFileAction, SIGNAL(triggered(bool)), this, SLOT(ImputApdlModelFile()));

    // import the simulate
    m_pImputFeamModelFileAction = new QAction(this);
    m_pImputFeamModelFileAction->setText(QString::fromLocal8Bit("ImportSimulate"));
    m_pImputFeamModelFileAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pImputFeamModelFileAction->setIcon(QIcon(":/Icon/Actions/imputSimulate.png"));
    connect(m_pImputFeamModelFileAction, SIGNAL(triggered(bool)), this, SLOT(ImputFeamModelFile()));

    // import the test
    m_pImputTestModelFileAction = new QAction(this);
    m_pImputTestModelFileAction->setText(QString::fromLocal8Bit("ImportTest"));
    m_pImputTestModelFileAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pImputTestModelFileAction->setIcon(QIcon(":/Icon/Actions/imputTest.png"));
    connect(m_pImputTestModelFileAction, SIGNAL(triggered(bool)), this, SLOT(ImputTestModelFile()));

    // output the word
    m_pOutputWordReportAction = new QAction(this);
    m_pOutputWordReportAction->setText(QString::fromLocal8Bit("Output Word"));
    m_pOutputWordReportAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pOutputWordReportAction->setIcon(QIcon(":/Icon/Actions/writeWord.png"));
    connect(m_pOutputWordReportAction, SIGNAL(triggered(bool)), this, SLOT(OutputWordReport()));

    // copy
    m_pCopyDataAction = new QAction(this);
    m_pCopyDataAction->setText(QString::fromLocal8Bit("Copy"));
    m_pCopyDataAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pCopyDataAction->setIcon(QIcon(":/Icon/Actions/Copy.png"));
    connect(m_pCopyDataAction, SIGNAL(triggered(bool)), this, SLOT(CopyData()));

    // cut
    m_pCutDataAction = new QAction(this);
    m_pCutDataAction->setText(QString::fromLocal8Bit("Cut"));
    m_pCutDataAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pCutDataAction->setIcon(QIcon(":/Icon/Actions/Cut.png"));
    connect(m_pCutDataAction, SIGNAL(triggered(bool)), this, SLOT(CutData()));

    // past
    m_pPastDataAction = new QAction(this);
    m_pPastDataAction->setText(QString::fromLocal8Bit("Past"));
    m_pPastDataAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pPastDataAction->setIcon(QIcon(":/Icon/Actions/Paste.png"));
    connect(m_pPastDataAction, SIGNAL(triggered(bool)), this, SLOT(PastData()));

    // delete
    m_pDeleteDataAction = new QAction(this);
    m_pDeleteDataAction->setText(QString::fromLocal8Bit("Delete"));
    m_pDeleteDataAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pDeleteDataAction->setIcon(QIcon(":/Icon/Actions/Delete.png"));
    connect(m_pDeleteDataAction, SIGNAL(triggered(bool)), this, SLOT(DeleteData()));

    // select all
    m_pSelectAllAction = new QAction(this);
    m_pSelectAllAction->setText(QString::fromLocal8Bit("Select All"));
    m_pSelectAllAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pSelectAllAction->setIcon(QIcon(":/Icon/Actions/SelectAll.png"));
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
    m_pShowMeshAction->setIcon(QIcon(":/Icon/Actions/mesh.png"));
    connect(m_pShowMeshAction, SIGNAL(triggered(bool)), this, SLOT(ShowMesh()));

    // tranparency
    m_pTransparencyAction = new QAction(this);
    m_pTransparencyAction->setText(QString::fromLocal8Bit("Tranporent"));
    m_pTransparencyAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pTransparencyAction->setIcon(QIcon(":/Icon/Actions/Transparant.png"));
    connect(m_pTransparencyAction, SIGNAL(triggered(bool)), this, SLOT(Transparency()));

    // show point
    m_pShowPointAction = new QAction(this);
    m_pShowPointAction->setText(QString::fromLocal8Bit("ShowPoint"));
    m_pShowPointAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pShowPointAction->setIcon(QIcon(":/Icon/Actions/ShowPoint.png"));
    connect(m_pShowPointAction, SIGNAL(triggered(bool)), this, SLOT(ShowPoint()));

    m_pShowPointNameAction = new QAction(this);
    m_pShowPointNameAction->setText(QString::fromLocal8Bit("ShowPointName"));
    m_pShowPointNameAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pShowPointNameAction->setIcon(QIcon(":/Icon/Actions/pointName.png"));
    connect(m_pShowPointNameAction, SIGNAL(triggered(bool)), this, SLOT(ShowPointName()));

    m_pShowDOFAction = new QAction(this);
    m_pShowDOFAction->setText(QString::fromLocal8Bit("DOF"));
    m_pShowDOFAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pShowDOFAction->setIcon(QIcon(":/Icon/Actions/DOF.png"));
    connect(m_pShowDOFAction, SIGNAL(triggered(bool)), this, SLOT(ShowDOF()));

    m_pLeftViewAction = new QAction(this);
    m_pLeftViewAction->setText(QString::fromLocal8Bit("Left"));
    m_pLeftViewAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pLeftViewAction->setIcon(QIcon(":/Icon/Actions/Left.png"));
    connect(m_pLeftViewAction, SIGNAL(triggered(bool)), this, SLOT(LeftView()));

    m_pRightViewAction = new QAction(this);
    m_pRightViewAction->setText(QString::fromLocal8Bit("Right"));
    m_pRightViewAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pRightViewAction->setIcon(QIcon(":/Icon/Actions/Right.png"));
    connect(m_pRightViewAction, SIGNAL(triggered(bool)), this, SLOT(RightView()));

    m_pButtonViewAction = new QAction(this);
    m_pButtonViewAction->setText(QString::fromLocal8Bit("Down"));
    m_pButtonViewAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pButtonViewAction->setIcon(QIcon(":/Icon/Actions/down.png"));
    connect(m_pButtonViewAction, SIGNAL(triggered(bool)), this, SLOT(ButtonView()));

    m_pTopViewAction = new QAction(this);
    m_pTopViewAction->setText(QString::fromLocal8Bit("Up"));
    m_pTopViewAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pTopViewAction->setIcon(QIcon(":/Icon/Actions/up.png"));
    connect(m_pTopViewAction, SIGNAL(triggered(bool)), this, SLOT(TopView()));

    m_pFrondViewAction = new QAction(this);
    m_pFrondViewAction->setText(QString::fromLocal8Bit("Front"));
    m_pFrondViewAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pFrondViewAction->setIcon(QIcon(":/Icon/Actions/Frond.png"));
    connect(m_pFrondViewAction, SIGNAL(triggered(bool)), this, SLOT(FrondView()));

    m_pBackViewAction = new QAction(this);
    m_pBackViewAction->setText(QString::fromLocal8Bit("Back"));
    m_pBackViewAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pBackViewAction->setIcon(QIcon(":/Icon/Actions/back.png"));
    connect(m_pBackViewAction, SIGNAL(triggered(bool)), this, SLOT(BackView()));

    m_pIOSViewAction = new QAction(this);
    m_pIOSViewAction->setText(QString::fromLocal8Bit("IOS"));
    m_pIOSViewAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pIOSViewAction->setIcon(QIcon(":/Icon/Actions/ios.png"));
    connect(m_pIOSViewAction, SIGNAL(triggered(bool)), this, SLOT(BackView()));

    m_pSelectFromAction = new QAction(this);
    m_pSelectFromAction->setText(QString::fromLocal8Bit("Fram"));
    m_pSelectFromAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pSelectFromAction->setIcon(QIcon(":/Icon/Actions/SelectForm.png"));
    connect(m_pSelectFromAction, SIGNAL(triggered(bool)), this, SLOT(BackView()));

    m_pSetToSelfAction = new QAction(this);
    m_pSetToSelfAction->setText(QString::fromLocal8Bit("Self"));
    m_pSetToSelfAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pSetToSelfAction->setIcon(QIcon(":/Icon/Actions/atuoChange.png"));
    connect(m_pSetToSelfAction, SIGNAL(triggered(bool)), this, SLOT(BackView()));

    // all the process
    m_pStaticsAnalysisAction = new QAction(this);
    m_pStaticsAnalysisAction->setText(QString::fromLocal8Bit("Analysis"));
    m_pStaticsAnalysisAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pStaticsAnalysisAction->setIcon(QIcon(":/Icon/Actions/AnalysisFEM.png"));
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
    m_pSetProgramAction->setIcon(QIcon(":/Icon/Actions/ModifyParameter.png"));
    connect(m_pSetProgramAction, SIGNAL(triggered(bool)), this, SLOT(SetProgram()));

    m_pSetTargetAction = new QAction(this);
    m_pSetTargetAction->setText(QString::fromLocal8Bit("Fixed Target"));
    m_pSetTargetAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pSetTargetAction->setIcon(QIcon(":/Icon/Actions/ModifyTarget.png"));
    connect(m_pSetTargetAction, SIGNAL(triggered(bool)), this, SLOT(SetTarget()));

    m_pAnalysisProgramAction = new QAction(this);
    m_pAnalysisProgramAction->setText(QString::fromLocal8Bit("Sensitivity Analysis"));
    m_pAnalysisProgramAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pAnalysisProgramAction->setIcon(QIcon(":/Icon/Actions/AnalysisSensitivity.png"));
    connect(m_pAnalysisProgramAction, SIGNAL(triggered(bool)), this, SLOT(AnalysisProgram()));

    m_pModelUpdatingAction = new QAction(this);
    m_pModelUpdatingAction->setText(QString::fromLocal8Bit("Updatting"));
    m_pModelUpdatingAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pModelUpdatingAction->setIcon(QIcon(":/Icon/Actions/updateModel.png"));
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
    m_pShowDataTreeAction->setIcon(QIcon(":/Icon/Actions/LeftWindow.png"));
    connect(m_pShowDataTreeAction, SIGNAL(triggered(bool)), this, SLOT(ShowDataTree()));

    m_pShowCommonAction = new QAction(this);
    m_pShowCommonAction->setText(QString::fromLocal8Bit("Common"));
    m_pShowCommonAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pShowCommonAction->setIcon(QIcon(":/Icon/Actions/downWindow.png"));
    connect(m_pShowCommonAction, SIGNAL(triggered(bool)), this, SLOT(ShowCommon()));

    m_pShowWindowsAsTabsAction = new QAction(this);
    m_pShowWindowsAsTabsAction->setText(QString::fromLocal8Bit("TabList"));
    m_pShowWindowsAsTabsAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pShowWindowsAsTabsAction->setIcon(QIcon(":/Icon/Actions/tablist.png"));
    connect(m_pShowWindowsAsTabsAction, SIGNAL(triggered(bool)), this, SLOT(ShowWindowsAsTabs()));

    m_pShowWindowsAsVerticalAction = new QAction(this);
    m_pShowWindowsAsVerticalAction->setText(QString::fromLocal8Bit("Horizontal"));
    m_pShowWindowsAsVerticalAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pShowWindowsAsVerticalAction->setIcon(QIcon(":/Icon/Actions/upDown.png"));
    connect(m_pShowWindowsAsVerticalAction, SIGNAL(triggered(bool)), this, SLOT(ShowWindowsAsVertical()));

    m_pShowWindowsAsHorizontalAction = new QAction(this);
    m_pShowWindowsAsHorizontalAction->setText(QString::fromLocal8Bit("Vertical"));
    m_pShowWindowsAsHorizontalAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pShowWindowsAsHorizontalAction->setIcon(QIcon(":/Icon/Actions/LeftRight.png"));
    connect(m_pShowWindowsAsHorizontalAction, SIGNAL(triggered(bool)), this, SLOT(ShowWindowsAsHorizontal()));

    m_pShowWindowsAsStackAcion = new QAction(this);
    m_pShowWindowsAsStackAcion->setText(QString::fromLocal8Bit("Stack"));
    m_pShowWindowsAsStackAcion->setShortcut(QKeySequence("Ctrl+O"));
    m_pShowWindowsAsStackAcion->setIcon(QIcon(":/Icon/Actions/StackWindow.png"));
    connect(m_pShowWindowsAsStackAcion, SIGNAL(triggered(bool)), this, SLOT(ShowWindowsAsStack()));

    // all the setting
    m_pSetSolverPathAction = new QAction(this);
    m_pSetSolverPathAction->setText(QString::fromLocal8Bit("Solver"));
    m_pSetSolverPathAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pSetSolverPathAction->setIcon(QIcon(":/Icon/Actions/ThirdSoftWarePath.png"));
    connect(m_pSetSolverPathAction, SIGNAL(triggered(bool)), this, SLOT(SetSolverPath()));

    m_pSetSeverAction = new QAction(this);
    m_pSetSeverAction->setText(QString::fromLocal8Bit("Server"));
    m_pSetSeverAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pSetSeverAction->setIcon(QIcon(":/Icon/Actions/ServerConfiguration.png"));
    connect(m_pSetSeverAction, SIGNAL(triggered(bool)), this, SLOT(SetSever()));

    m_pSetBaseAction = new QAction(this);
    m_pSetBaseAction->setText(QString::fromLocal8Bit("BaseSet"));
    m_pSetBaseAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pSetBaseAction->setIcon(QIcon(":/Icon/Actions/Setting.png"));
    connect(m_pSetBaseAction, SIGNAL(triggered(bool)), this, SLOT(SetBase()));

    m_pSetShortcutAction = new QAction(this);
    m_pSetShortcutAction->setText(QString::fromLocal8Bit("ShortCut"));
    m_pSetShortcutAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pSetShortcutAction->setIcon(QIcon(":/Icon/Actions/ShortCut.png"));
    connect(m_pSetShortcutAction, SIGNAL(triggered(bool)), this, SLOT(SetShortCutAction()));

    // all the help manual
    m_pInstallManualAction = new QAction(this);
    m_pInstallManualAction->setText(QString::fromLocal8Bit("Install Manual"));
    m_pInstallManualAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pInstallManualAction->setIcon(QIcon(":/Icon/Actions/InstallDoc.png"));
    connect(m_pInstallManualAction, SIGNAL(triggered(bool)), this, SLOT(InstallManual()));

    m_pTrainManualAction = new QAction(this);
    m_pTrainManualAction->setText(QString::fromLocal8Bit("Training Manual"));
    m_pTrainManualAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pTrainManualAction->setIcon(QIcon(":/Icon/Actions/BasicTrainDoc.png"));
    connect(m_pTrainManualAction, SIGNAL(triggered(bool)), this, SLOT(TrainManual()));

    m_pTheoryAction = new QAction(this);
    m_pTheoryAction->setText(QString::fromLocal8Bit("Theory Manual"));
    m_pTheoryAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pTheoryAction->setIcon(QIcon(":/Icon/Actions/TheoryDoc.png"));
    connect(m_pTheoryAction, SIGNAL(triggered(bool)), this, SLOT(TheoryManual()));

    m_pUserAction = new QAction(this);
    m_pUserAction->setText(QString::fromLocal8Bit("User Manual"));
    m_pUserAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pUserAction->setIcon(QIcon(":/Icon/Actions/UserDoc.png"));
    connect(m_pUserAction, SIGNAL(triggered(bool)), this, SLOT(UserManual()));

    m_pLicenseAction = new QAction(this);
    m_pLicenseAction->setText(QString::fromLocal8Bit("License"));
    m_pLicenseAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pLicenseAction->setIcon(QIcon(":/Icon/Actions/LicenseInfo.png"));
    connect(m_pLicenseAction, SIGNAL(triggered(bool)), this, SLOT(LicenseInformation()));

    m_pLearningOnlineAction = new QAction(this);
    m_pLearningOnlineAction->setText(QString::fromLocal8Bit("Learnning On Line"));
    m_pLearningOnlineAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pLearningOnlineAction->setIcon(QIcon(":/Icon/Actions/OnlineLearning.png"));
    connect(m_pLearningOnlineAction, SIGNAL(triggered(bool)), this, SLOT(LearningOnline()));

    m_pConnectAction = new QAction(this);
    m_pConnectAction->setText(QString::fromLocal8Bit("Connect Us"));
    m_pConnectAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pConnectAction->setIcon(QIcon(":/Icon/Actions/ContactUs.png"));
    connect(m_pConnectAction, SIGNAL(triggered(bool)), this, SLOT(ConnectionUs()));

    m_pAboutAction = new QAction(this);
    m_pAboutAction->setText(QString::fromLocal8Bit("About SimVVer"));
    m_pAboutAction->setShortcut(QKeySequence("Ctrl+O"));
    m_pAboutAction->setIcon(QIcon(":/Icon/Actions/AboutSimVVer.png"));
    connect(m_pAboutAction, SIGNAL(triggered(bool)), this, SLOT(AboutUs()));

    m_pExitAction = new QAction(this);
    m_pExitAction->setText(QString::fromLocal8Bit("Close"));
    m_pExitAction->setShortcut(QKeySequence(Qt::Key_Exit));
    m_pExitAction->setIcon(QIcon(":/Icon/Actions/Quit.png"));
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
    this->addToolBar(Qt::TopToolBarArea, m_pMainToolBar);

    m_pViewToolBar = new QToolBar(this);
    this->addToolBar(Qt::RightToolBarArea, m_pViewToolBar);
}

void MainWindow::addMenusToMenuBar()
{
   m_pMenuBar->addMenu(m_pFileMenu);
   m_pMenuBar->addMenu(m_pEditMenu);
   m_pMenuBar->addMenu(m_pViewMenu);
   m_pMenuBar->addMenu(m_pProcessMenu);
   m_pMenuBar->addMenu(m_pProgramSetMenu);
   m_pMenuBar->addMenu(m_pToolMenu);
   m_pMenuBar->addMenu(m_pWindMenu);
   m_pMenuBar->addMenu(m_pSetUpMenu);
   m_pMenuBar->addMenu(m_pAboutMenu);
   m_pMenuBar->addMenu(m_pHelpManualMenu);
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

// set Graphic window as the current wind
void MainWindow::setAsGraphicWind()
{
//    if (  ) {
//    } else {
//    }
}

// set as Table window as the current wind
void MainWindow::setAsTableWind()
{
//    if (  ) {
//    } else {
//    }
}

// set as curve window as the current wind
void MainWindow::setAsCurveWind()
{
//    if (  ) {
//    } else {
//    }
}

void MainWindow::CreateNewGraphicWindow()
{
    m_pCurrentGraphicWind = new GraphicMdiSubWin(this);
    m_MdiAreaWidget->addSubWindow(m_pCurrentGraphicWind);
    m_pCurrentGraphicWind->showMaximized();
    m_pGL = m_pCurrentGraphicWind->m_pGLWidget;
}

void MainWindow::CreateNewTableWindow()
{
    m_pCurrentTableWind = new TableMdiSubWin(this);
    m_MdiAreaWidget->addSubWindow(m_pCurrentTableWind);
}

void MainWindow::CreateNewCurveWindow()
{
    m_pCurrentCurveWind = new CurveMdiSubWin(this);
    m_MdiAreaWidget->addSubWindow(m_pCurrentCurveWind);
}

//void MainWindow::switchTransparency()
//{
////    m_pGL->switchTransparency();
//}

void MainWindow::addActionsToMenu()
{
    // all the file
    m_pFileMenu->addAction(m_pOpenFileAction);
}

//void MainWindow::showPointSwitch()
//{
////    m_pGL->showPointSwitch();
//}

//void MainWindow::showLineSwith()
//{
////    m_pGL->showLineSwitch();
//}

//void MainWindow::showMeshSwitch()
//{
////    m_pGL->showMeshSwitch();
//}

//void MainWindow::showFaceSwitch()
//{
////    m_pGL->showFaceSwitch();
//}

void MainWindow::openFile() {
    QString _filePath = QFileDialog::getOpenFileName(this, QDir::currentPath(), QDir::currentPath(),
                                                     QString("STL(*.stl);;BDF(*.bdf);;CBD(*.cbd);;File(*.*)"));

    if (_filePath.endsWith(".bdf",Qt::CaseInsensitive)) {
        m_pGL->clearAllData();  // clear all the gl data
        m_pBdfFile->clearAllData();
        emit startReadBDF(_filePath); // read file in a thread
    } else if (_filePath.endsWith(".cdb",Qt::CaseInsensitive)) {
        m_pGL->clearAllData();  // clear all the gl data
        m_pCbdFile->clearAllData();
        emit startReadCDB(_filePath);
    } else if (_filePath.endsWith(".stl",Qt::CaseInsensitive)) {
        m_pGL->clearAllData();  // clear all the gl data
        m_pSTLFile->clearAllData();
        emit startReadSTL(_filePath);
    } else { // can't analysis this format file
        return;
    }
}

void MainWindow::SaveFile()
{
}

void MainWindow::SaveAsFile()
{
    QString _filepath = QFileDialog::getSaveFileName(this,
                                                     QString::fromLocal8Bit(""),
                                                     QString::fromLocal8Bit(""),
                                                     "Project(*.project);;Feam(*.bdf *.cbd);;Test(*.uff *.unv)");
    if ( _filepath.isEmpty() ) {
        QMessageBox _messageBox;
        _messageBox.setIcon(QMessageBox::Warning);
        _messageBox.setWindowTitle("Warnning!!");
        _messageBox.setText("you have not select file,\n"
                            "please reselect file");
        _messageBox.addButton(QMessageBox::Ok);
        _messageBox.setButtonText(QMessageBox::Ok, QString("OK"));
        _messageBox.exec();
    }
}

void MainWindow::SetWorkSpace()
{
}

void MainWindow::ImputApdlModelFile()
{
    QString _filepath = QFileDialog::getOpenFileName(this,
                                                     QString::fromLocal8Bit(""),
                                                     QString::fromLocal8Bit(""),
                                                     "Project(*.project);;Feam(*.bdf *.cbd);;Test(*.uff *.unv)");
    if ( _filepath.isEmpty() ) {
        QMessageBox _messageBox;
        _messageBox.setIcon(QMessageBox::Warning);
        _messageBox.setWindowTitle("Warnning!!");
        _messageBox.setText("you have not select file,\n"
                            "please reselect file");
        _messageBox.addButton(QMessageBox::Ok);
        _messageBox.setButtonText(QMessageBox::Ok, QString("OK"));
        _messageBox.exec();
    }
}

void MainWindow::ImputFeamModelFile()
{
    QString _filePath = QFileDialog::getOpenFileName(this,
                                                     QString::fromLocal8Bit(""),
                                                     QString::fromLocal8Bit(""),
                                                     "Feam(*.bdf *.cdb);;Project(*.project);;Test(*.uff *.unv)");
    if ( _filePath.isEmpty() ) {  // doesn't select fem file
        QMessageBox _messageBox;
        _messageBox.setIcon(QMessageBox::Warning);
        _messageBox.setWindowTitle("Warnning!!");
        _messageBox.setText("you have not select file,\n"
                            "please reselect file");
        _messageBox.addButton(QMessageBox::Ok);
        _messageBox.setButtonText(QMessageBox::Ok, QString("OK"));
        _messageBox.exec();
    }

    if (_filePath.endsWith(".bdf",Qt::CaseInsensitive)) {
//        m_pGL->clearAllData();  // clear all the gl data
        m_pBdfFile->clearAllData();
        emit startReadBDF(_filePath); // read file in a thread
    } else if (_filePath.endsWith(".cdb",Qt::CaseInsensitive)) {
        CBDFile _cbdFile;
        if ( _cbdFile.ReadFile(_filePath) ) {
            m_pGL->swapData(_cbdFile.m_vCenter,
                            _cbdFile.m_fRange,
                            _cbdFile.m_vVertexs,
                            _cbdFile.m_vVertexsColor,
                            _cbdFile.m_vVertexsIndex,
                            _cbdFile.m_vLineVertexs,
                            _cbdFile.m_vLineColor,
                            _cbdFile.m_vLineNormal,
                            _cbdFile.m_vLineIndex,
                            _cbdFile.m_vTrianglesVertexs,
                            _cbdFile.m_vTrianglesNormal,
                            _cbdFile.m_vTrianglesColor,
                            _cbdFile.m_vTriangleIndex,
                            _cbdFile.m_vQuadsVertexs,
                            _cbdFile.m_vQuadsColor,
                            _cbdFile.m_vQuadsNormal,
                            _cbdFile.m_vQuadsIndex);
            _cbdFile.clearAllData();  // clear all the old data
        }
    } else { // can't analysis this format file
        return;
    }
}

void MainWindow::ImputTestModelFile()
{
    QString _filePath = QFileDialog::getOpenFileName(this,
                                                     QString::fromLocal8Bit(""),
                                                     QString::fromLocal8Bit(""),
                                                     "Test(*.uff *.unv *.txt);;Project(*.project)");
    if ( _filePath.isEmpty() ) {
        QMessageBox _messageBox;
        _messageBox.setIcon(QMessageBox::Warning);
        _messageBox.setWindowTitle("Warnning!!");
        _messageBox.setText("you have not select file,\n"
                            "please reselect file");
        _messageBox.addButton(QMessageBox::Ok);
        _messageBox.setButtonText(QMessageBox::Ok, QString("OK"));
        _messageBox.exec();
    }

    if (_filePath.endsWith(".txt",Qt::CaseInsensitive)) {
        m_pTxtFile->clearAllData();
        emit startReadTXT(_filePath); // read file in a thread
    } else if (_filePath.endsWith(".cdb",Qt::CaseInsensitive)) {
        CBDFile _cbdFile;
        if ( _cbdFile.ReadFile(_filePath) ) {
            m_pGL->swapData(_cbdFile.m_vCenter,
                            _cbdFile.m_fRange,
                            _cbdFile.m_vVertexs,
                            _cbdFile.m_vVertexsColor,
                            _cbdFile.m_vVertexsIndex,
                            _cbdFile.m_vLineVertexs,
                            _cbdFile.m_vLineColor,
                            _cbdFile.m_vLineNormal,
                            _cbdFile.m_vLineIndex,
                            _cbdFile.m_vTrianglesVertexs,
                            _cbdFile.m_vTrianglesNormal,
                            _cbdFile.m_vTrianglesColor,
                            _cbdFile.m_vTriangleIndex,
                            _cbdFile.m_vQuadsVertexs,
                            _cbdFile.m_vQuadsColor,
                            _cbdFile.m_vQuadsNormal,
                            _cbdFile.m_vQuadsIndex);
            _cbdFile.clearAllData();  // clear all the old data
        }
    } else { // can't analysis this format file
        return;
    }
}

// new GraphicWindow
void MainWindow::newGraphicMdiSubWin()
{
    m_pCurrentGraphicWind = new GraphicMdiSubWin(m_MdiAreaWidget);
//    m_pGL = m_pCurrentGraphicWind->m_pGLWidget;
    m_MdiAreaWidget->addSubWindow(m_pCurrentGraphicWind);
    m_pCurrentGraphicWind->setAttribute(Qt::WA_DeleteOnClose);
    m_pCurrentGraphicWind->showMaximized();
}

// new TableWindow
void MainWindow::newTableMdiSubWin()
{
    m_pCurrentTableWind = new TableMdiSubWin(m_MdiAreaWidget);
    m_MdiAreaWidget->addSubWindow(m_pCurrentTableWind);
    m_pCurrentTableWind->setAttribute(Qt::WA_DeleteOnClose);
    m_pCurrentTableWind->showMaximized();
}

// new CurveWindow
void MainWindow::newCurveMdiSubWin()
{
    m_pCurrentCurveWind = new CurveMdiSubWin(m_MdiAreaWidget);
    m_MdiAreaWidget->addSubWindow(m_pCurrentCurveWind);
    m_pCurrentCurveWind->setAttribute(Qt::WA_DeleteOnClose);
    m_pCurrentCurveWind->showMaximized();
}

// show as a current window
void MainWindow::showGraphicWidget()
{
    if ( m_pCurrentGraphicWind != nullptr ) {
        m_pCurrentGraphicWind->show();
    } else {
        newGraphicMdiSubWin();
    }
}

void MainWindow::showTableWidget()
{
    if ( m_pCurrentTableWind != nullptr ) {
        m_pCurrentTableWind->show();
    } else {
        newTableMdiSubWin();
    }
}

void MainWindow::showCarveWidget()
{
    if ( m_pCurrentCurveWind != nullptr ) {
        m_pCurrentCurveWind->show();
    } else {
        newCurveMdiSubWin();
    }
}

void MainWindow::OutputWordReport()
{
}

void MainWindow::CopyData()
{
}

void MainWindow::CutData()
{
}

void MainWindow::PastData()
{
}

void MainWindow::DeleteData()
{
}

void MainWindow::SelectAll()
{
}

void MainWindow::Unselect()
{
}

void MainWindow::ShowDataTree()
{
}

void MainWindow::ShowCommon()
{
}

void MainWindow::ShowMesh()
{
    if (m_pGL != nullptr) {
        m_pGL->showMeshSwitch();
    }
}

void MainWindow::Transparency()
{
    if ( m_pGL != nullptr ) {
        m_pGL->switchTransparency();
    }
}

void MainWindow::ShowPoint()
{
    if ( m_pGL != nullptr ) {
        m_pGL->showPointSwitch();
    }
}

void MainWindow::ShowPointName()
{
}

void MainWindow::ShowDOF()
{
}

void MainWindow::LeftView()
{
}

void MainWindow::RightView()
{
}

void MainWindow::ButtonView()
{
}

void MainWindow::TopView()
{
}

void MainWindow::FrondView()
{
}

void MainWindow::BackView()
{
}

void MainWindow::StaticsAnalysis()
{
}

void MainWindow::MeshConvergence()
{
}

void MainWindow::CorrelationAnalysis()
{
}

void MainWindow::SetProgram()
{
}

void MainWindow::SetTarget()
{
}

void MainWindow::AnalysisProgram()
{
}

void MainWindow::ModelUpdating()
{
}

void MainWindow::ScreenShort()
{
}

void MainWindow::ShowWindowsAsTabs()
{
}

void MainWindow::ShowWindowsAsVertical()
{
}

void MainWindow::ShowWindowsAsHorizontal()
{
}

void MainWindow::ShowWindowsAsStack()
{
}

void MainWindow::SetSolverPath()
{
}

void MainWindow::SetSever()
{
}

void MainWindow::SetBase()
{
}

void MainWindow::SetShortCutAction()
{
}

void MainWindow::InstallManual()
{
}

void MainWindow::TrainManual()
{
}

void MainWindow::TheoryManual()
{
}

void MainWindow::UserManual()
{
}

void MainWindow::LicenseInformation()
{
}

void MainWindow::LearningOnline()
{
}

void MainWindow::ConnectionUs()
{
}

void MainWindow::AboutUs()
{
}

void MainWindow::closeEvent(QCloseEvent *event_)
{
    QMessageBox _messageBox;
    _messageBox.setIcon(QMessageBox::Warning);
    _messageBox.setWindowTitle("Warnning!!");
    _messageBox.setText("Do you want to exit the application\n"
                        "yes / no");
    _messageBox.addButton(QMessageBox::Yes);
    _messageBox.addButton(QMessageBox::No);
    _messageBox.setButtonText(QMessageBox::Yes, QString("YES"));
    _messageBox.setButtonText(QMessageBox::No, QString("NO"));
    QMessageBox::StandardButton _standbt = static_cast<QMessageBox::StandardButton>(_messageBox.exec());

    switch (_standbt) {
    case QMessageBox::Yes:
        event_->accept();
        break;

    case QMessageBox::No:
        event_->ignore();
        break;

    default:
        event_->ignore();
        break;
    }
}

void MainWindow::updateBDFToOpenGL()
{
    m_pGL->swapData( m_pBdfFile->m_vCenter,
                     m_pBdfFile->m_fRange,
                     m_pBdfFile->m_vVertexs,
                     m_pBdfFile->m_vVertexsColor,
                     m_pBdfFile->m_vVertexsIndex,
                     m_pBdfFile->m_vLineVertexs,
                     m_pBdfFile->m_vLineColor,
                     m_pBdfFile->m_vLineNormal,
                     m_pBdfFile->m_vLineIndex,
                     m_pBdfFile->m_vTrianglesVertexs,
                     m_pBdfFile->m_vTrianglesColor,
                     m_pBdfFile->m_vTrianglesNormal,
                     m_pBdfFile->m_vTriangleIndex,
                     m_pBdfFile->m_vQuadsVertexs,
                     m_pBdfFile->m_vQuadsColor,
                     m_pBdfFile->m_vQuadsNormal,
                     m_pBdfFile->m_vQuadsIndex );
    m_pGL->update();
}

void MainWindow::updateTxtToOpenGL()
{
    m_pGL->swapData( m_pTxtFile->m_vCenter,
                     m_pTxtFile->m_fRange,
                     m_pTxtFile->m_vVertexs,
                     m_pTxtFile->m_vVertexsColor,
                     m_pTxtFile->m_vVertexsIndex,
                     m_pTxtFile->m_vLineVertexs,
                     m_pTxtFile->m_vLineColor,
                     m_pTxtFile->m_vLineNormal,
                     m_pTxtFile->m_vLineIndex,
                     m_pTxtFile->m_vTrianglesVertexs,
                     m_pTxtFile->m_vTrianglesColor,
                     m_pTxtFile->m_vTrianglesNormal,
                     m_pTxtFile->m_vTriangleIndex,
                     m_pTxtFile->m_vQuadsVertexs,
                     m_pTxtFile->m_vQuadsColor,
                     m_pTxtFile->m_vQuadsNormal,
                     m_pTxtFile->m_vQuadsIndex );
    m_pGL->update();
}

void MainWindow::updateSTLToOpenGL()
{
    m_pGL->swapData( m_pSTLFile->m_vCenter,
                     m_pSTLFile->m_fRange,
                     m_pSTLFile->m_vVertexs,
                     m_pSTLFile->m_vVertexsColor,
                     m_pSTLFile->m_vVertexsIndex,
                     m_pSTLFile->m_vLineVertexs,
                     m_pSTLFile->m_vLineColor,
                     m_pSTLFile->m_vLineNormal,
                     m_pSTLFile->m_vLineIndex,
                     m_pSTLFile->m_vTrianglesVertexs,
                     m_pSTLFile->m_vTrianglesColor,
                     m_pSTLFile->m_vTrianglesNormal,
                     m_pSTLFile->m_vTriangleIndex,
                     m_pSTLFile->m_vQuadsVertexs,
                     m_pSTLFile->m_vQuadsColor,
                     m_pSTLFile->m_vQuadsNormal,
                     m_pSTLFile->m_vQuadsIndex );
    m_pGL->update();
}

void MainWindow::createShowVectors()
{
    m_pGL->swapData( m_pBdfFile->m_vCenter,
                     m_pBdfFile->m_fRange,
                     m_pBdfFile->m_vVertexs,
                     m_pBdfFile->m_vVertexsColor,
                     m_pBdfFile->m_vVertexsIndex,
                     m_pBdfFile->m_vLineVertexs,
                     m_pBdfFile->m_vLineColor,
                     m_pBdfFile->m_vLineNormal,
                     m_pBdfFile->m_vLineIndex,
                     m_pBdfFile->m_vTrianglesVertexs,
                     m_pBdfFile->m_vTrianglesColor,
                     m_pBdfFile->m_vTrianglesNormal,
                     m_pBdfFile->m_vTriangleIndex,
                     m_pBdfFile->m_vQuadsVertexs,
                     m_pBdfFile->m_vQuadsColor,
                     m_pBdfFile->m_vQuadsNormal,
                     m_pBdfFile->m_vQuadsIndex );
    m_pGL->update();
}

MainWindow::~MainWindow() {
    if ( m_pBdfFile != nullptr ) {
        delete  m_pBdfFile;
        m_pBdfFile = nullptr;
    }
    if ( m_pCbdFile != nullptr ) {
        delete m_pCbdFile;
        m_pCbdFile = nullptr;
    }

    if ( m_pTxtFile != nullptr ) {
        delete m_pTxtFile;
        m_pTxtFile = nullptr;
    }

    if ( m_pSTLFile != nullptr ){
        delete m_pSTLFile;
        m_pSTLFile = nullptr;
    }

    // start delete the thread
    m_pReadBDFThread->quit();
    m_pReadCBDThread->quit();
    m_pReadTxtThread->quit();
    m_pReadSTLThread->quit();

    while (m_pReadBDFThread->isRunning()) {
        QApplication::processEvents();
    }
    while (m_pReadCBDThread->isRunning()) {
        QApplication::processEvents();
    }
    while (m_pReadTxtThread->isRunning()) {
        QApplication::processEvents();
    }
    while (m_pReadTxtThread->isRunning()) {
        QApplication::processEvents();
    }
    m_pReadBDFThread->wait();
    m_pReadCBDThread->wait();
    m_pReadTxtThread->wait();
    m_pReadSTLThread->wait();

    if (m_pReadBDFThread != nullptr) {
        delete m_pReadBDFThread;
        m_pReadBDFThread = nullptr;
    }

    if (m_pReadCBDThread != nullptr) {
        delete m_pReadCBDThread;
        m_pReadCBDThread = nullptr;
    }

    if (m_pReadTxtThread != nullptr) {
        delete m_pReadTxtThread;
        m_pReadTxtThread = nullptr;
    }

    if (m_pReadSTLThread != nullptr) {
        delete m_pReadSTLThread;
        m_pReadSTLThread = nullptr;
    }
}
