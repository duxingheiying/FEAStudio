#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtConcurrent>
#include <QFuture>

class GraphicMdiSubWin;
class TableMdiSubWin;
class CurveMdiSubWin;

class QAction;
class GLWidget;
class MessageDockWidget;
class TreeDockWidget;
class PropertyDockWidget;
class QMdiArea;

class AnalysisFile;
class BDFFile;
class CBDFile;
class TxtFile;
class STLFile;

namespace Ui {
class MainWindow;
}

class   MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() override;

protected:
    void closeEvent(QCloseEvent*event_) override; // close the mainwindow

private:
    void createAction();  // create actions
    void createMenu();  // create menus
    void createToolbars();
    void addActiontosToToolBar();  // add actions to bar
    void addActionsToMenu();  // add actions to menu
    void addMenusToMenuBar();  // add menu to bar
    void setAsGraphicWind(); // set Graphic window as the current wind
    void setAsTableWind(); // set Table window as the current wind
    void setAsCurveWind(); // set Curve window as the current wind
    void CreateNewGraphicWindow(); // create new graphic Window
    void CreateNewTableWindow(); // create new Table Window
    void CreateNewCurveWindow(); // create new Curve Window

public:

private:
    // toolbars
    QToolBar* m_pViewToolBar;

    // file
    QMenu *m_pFileMenu; // file menue
    QAction *m_pOpenFileAction;  // open file action
    QAction *m_pSaveFileAction;
    QAction *m_pSAveAsFileAction;
    QAction *m_pSetWorkSpaceAction;
    QAction *m_pImputApdlModelFileAction;
    QAction *m_pImputFeamModelFileAction;
    QAction *m_pImputTestModelFileAction;
    QAction *m_pOutputWordReportAction;

    // edit
    QMenu *m_pEditMenu; // edit menu
    QAction *m_pCopyDataAction;
    QAction *m_pCutDataAction;
    QAction *m_pPastDataAction;
    QAction *m_pDeleteDataAction;
    QAction *m_pSelectAllAction;
    QAction *m_pUnselectAction;

    // view
    QMenu *m_pViewMenu; // view menu
    QAction *m_pShowDataTreeAction;
    QAction *m_pShowCommonAction;
    QAction *m_pShowMeshAction;
    QAction *m_pTransparencyAction;
    QAction *m_pShowPointAction;
    QAction *m_pShowPointNameAction;
    QAction *m_pShowDOFAction;
    QAction *m_pLeftViewAction;
    QAction *m_pRightViewAction;
    QAction *m_pButtonViewAction;
    QAction *m_pTopViewAction;
    QAction *m_pFrondViewAction;
    QAction *m_pBackViewAction;
    QAction *m_pIOSViewAction;
    QAction *m_pSelectFromAction;
    QAction *m_pSetToSelfAction;

    // process
    QMenu *m_pProcessMenu;  // process menu
    QAction *m_pStaticsAnalysisAction;
    QAction *m_pMeshConvergenceAction;
    QAction *m_pCorrelationAnalysisAction;

    QMenu *m_pProgramSetMenu;
    QAction *m_pSetProgramAction;
    QAction *m_pSetTargetAction;
    QAction *m_pAnalysisProgramAction;
    QAction *m_pModelUpdatingAction;

    // tools
    QMenu *m_pToolMenu;
    QAction *m_pScreenShortAction;

    // windows
    QMenu *m_pWindMenu;
    QAction *m_pShowWindowsAsTabsAction;
    QAction *m_pShowWindowsAsVerticalAction;
    QAction *m_pShowWindowsAsHorizontalAction;
    QAction *m_pShowWindowsAsStackAcion;

    // setup
    QMenu *m_pSetUpMenu;
    QAction *m_pSetSolverPathAction;
    QAction *m_pSetSeverAction;
    QAction *m_pSetBaseAction;
    QAction *m_pSetShortcutAction;

    // about
    QMenu *m_pAboutMenu;

    // second floor menu
    QMenu *m_pHelpManualMenu;

    // second floot actions
    QAction *m_pInstallManualAction;
    QAction *m_pTrainManualAction;
    QAction *m_pTheoryAction;
    QAction *m_pUserAction;

    // top actions
    QAction *m_pLicenseAction;
    QAction *m_pLearningOnlineAction;
    QAction *m_pConnectAction;
    QAction *m_pAboutAction;
    QAction* m_pExitAction;

    // widget
    QMainWindow* m_pCenterMainWindow;
    QMdiArea* m_MdiAreaWidget;

    GraphicMdiSubWin* m_pCurrentGraphicWind;
    TableMdiSubWin* m_pCurrentTableWind;
    CurveMdiSubWin* m_pCurrentCurveWind;

    MessageDockWidget* m_pMSDockWidget;  // message box widet
    TreeDockWidget* m_pTreeDockWidget;  // data tree widget
    PropertyDockWidget* m_pPropertyDockWidget;  // property widget

    // analisys files
    AnalysisFile* m_pBdfFile{nullptr};
    AnalysisFile* m_pCbdFile{nullptr};
    TxtFile* m_pTxtFile{nullptr};
    STLFile* m_pSTLFile{nullptr};

    QThread* m_pReadBDFThread{nullptr};
    QThread* m_pReadCBDThread{nullptr};
    QThread* m_pReadTxtThread{nullptr};
    QThread* m_pReadSTLThread{nullptr};

    GLWidget* m_pGL;

private slots:
    void openFile();
//    void showPointSwitch();
//    void showLineSwith();
//    void showMeshSwitch();
//    void showFaceSwitch();
//    void switchTransparency();

//    void OpenFile();
    void SaveFile();
    void SaveAsFile();
    void SetWorkSpace();
    void ImputApdlModelFile();
    void ImputFeamModelFile();
    void ImputTestModelFile();
    void OutputWordReport();

    void CopyData();
    void CutData();
    void PastData();
    void DeleteData();
    void SelectAll();
    void Unselect();

    void ShowDataTree();
    void ShowCommon();
    void ShowMesh();
    void Transparency();
    void ShowPoint();
    void ShowPointName();
    void ShowDOF();
    void LeftView();
    void RightView();
    void ButtonView();
    void TopView();
    void FrondView();
    void BackView();

    void StaticsAnalysis();
    void MeshConvergence();
    void CorrelationAnalysis();
    void SetProgram();
    void SetTarget();
    void AnalysisProgram();
    void ModelUpdating();

    void ScreenShort();

    void ShowWindowsAsTabs();
    void ShowWindowsAsVertical();
    void ShowWindowsAsHorizontal();
    void ShowWindowsAsStack();

    void SetSolverPath();
    void SetSever();
    void SetBase();
    void SetShortCutAction();

    void InstallManual();
    void TrainManual();
    void TheoryManual();
    void UserManual();
    void LicenseInformation();
    void LearningOnline();
    void ConnectionUs();
    void AboutUs();

    // show as a current window
    void showGraphicWidget();
    void showTableWidget();
    void showCarveWidget();
    void newGraphicMdiSubWin();
    void newTableMdiSubWin();
    void newCurveMdiSubWin();

signals:
    void startReadBDF(const QString&);
    void startReadCDB(const QString&);
    void startReadTXT(const QString&);
    void startReadSTL(const QString&);

public slots:
    void updateBDFToOpenGL();
    void updateTxtToOpenGL();
    void updateSTLToOpenGL();
    void createShowVectors();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
