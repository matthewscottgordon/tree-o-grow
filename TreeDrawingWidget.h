#ifndef TREE_DRAWING_WIDGET_H
#define TREE_DRAWING_WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>


class TreeDrawingWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
public:
    TreeDrawingWidget( QWidget *parent );

protected:
    void initializeGL() override;
    void resizeGL( int width, int height ) override;
    void paintGL() override;

private:
    void compileShaders();
    
    GLuint m_treeVao;
    GLuint m_treeVertexBuffer;

    GLuint m_shaderProgram;
    GLuint m_positionAttribLocation;
    GLuint m_projectionModelViewMatrixLocation;
};

#endif
