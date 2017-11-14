#include "TreeDrawingWidget.h"

#include "TreeLines.frag.h"
#include "TreeLines.vert.h"

#include <cassert>
#include <iostream>

static constexpr GLint VERTICES_PER_TRIANGLE = 3;
static constexpr GLint ELEMENTS_PER_VERTEX = 3;
static constexpr GLint TEST_TREE_NUM_TRIANGLES = 2;
static constexpr GLint TEST_TREE_BUFFER_LENGTH =
    ELEMENTS_PER_VERTEX * VERTICES_PER_TRIANGLE * TEST_TREE_NUM_TRIANGLES;

static constexpr const GLchar *vertexShaderSource = R""""(
    #version 330 core
 
    const mat4 projectionModelViewMatrix = mat4( 1,  0,  0,  0,
                                                 0,  0, -1,  0,
                                                 0,  1,  0,  0,
                                                 0,  0,  0,  1 );
 
    in vec3 position;
 
    void main()
    {
        gl_Position = projectionModelViewMatrix * vec4(position, 1.0);
    }
    )"""";


static constexpr const GLchar *fragmentShaderSource = R""""(
    #version 330 core
 
    out vec4 colorOut;
 
    void main()
    {
        colorOut = vec4( 0.0, 0.0, 0.0, 1.0 );
    }
    )"""";


TreeDrawingWidget::TreeDrawingWidget( QWidget *parent )
    : QOpenGLWidget(parent)
{
}


void TreeDrawingWidget::initializeGL()
{
    auto glVersion = QOpenGLContext::currentContext()->format().version();
    std::cerr<<"Open GL "<<glVersion.first<<'.'<<glVersion.second<<std::endl;
    initializeOpenGLFunctions();
    
    compileShaders();
    glClearColor( 0.5, 0.5, 1.0, 1.0 );
    
    glGenVertexArrays( 1, &m_treeVao );
    glBindVertexArray(m_treeVao);
    glGenBuffers( 1, &m_treeVertexBuffer );
    glBindBuffer( GL_ARRAY_BUFFER, m_treeVertexBuffer );
    static const float testTreeVertices[TEST_TREE_BUFFER_LENGTH] = {
         0.5,  0.0, 0.0,
         0.0,  0.0, 1.0,
        -0.5,  0.0, 0.0,
         0.0,  0.5, 0.0,
         0.0,  0.0, 1.0,
         0.0, -0.5, 0.0 };
    glBufferData(GL_ARRAY_BUFFER, sizeof(testTreeVertices), testTreeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(m_positionAttribLocation);
    glVertexAttribPointer( m_positionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
}


void TreeDrawingWidget::resizeGL( int width, int height )
{
}


void TreeDrawingWidget::paintGL()
{
    glUseProgram(m_shaderProgram);
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glBindVertexArray(m_treeVao);
    glDrawArrays(GL_TRIANGLES, 0, VERTICES_PER_TRIANGLE*TEST_TREE_NUM_TRIANGLES);
}


void TreeDrawingWidget::compileShaders()
{
    const GLint vertexShaderSourceLength = strlen(vertexShaderSource);
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource( vertexShader, 1, &vertexShaderSource, &vertexShaderSourceLength );
    glCompileShader(vertexShader);
    GLint success = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if( success == GL_FALSE )
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        //The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
        std::cerr<<infoLog.data()<<std::endl;
    }

    
    const GLint fragmentShaderSourceLength = strlen(fragmentShaderSource);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource( fragmentShader, 1, &fragmentShaderSource, &fragmentShaderSourceLength );
    glCompileShader(fragmentShader);
    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
    assert(success!=GL_FALSE);


    m_shaderProgram = glCreateProgram();
    glAttachShader( m_shaderProgram, vertexShader );
    glAttachShader( m_shaderProgram, fragmentShader );
    glBindFragDataLocation(m_shaderProgram, 0, "colorOut");
    glLinkProgram(m_shaderProgram);
    glGetProgramiv( m_shaderProgram, GL_LINK_STATUS, &success );
    assert(success!=GL_FALSE);

    m_positionAttribLocation = glGetAttribLocation( m_shaderProgram, "position" );

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
