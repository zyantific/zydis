static const ZydisInstructionEncodingInfo INSTR_ENCODINGS[] = 
{
    {
        .flags =  0,
        .disp =  {
            .size =  {
                0,
                0,
                0
            }
        },
        .imm =  {
            [0] =  {
                .size =  {
                    0,
                    0,
                    0
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            },
            [1] =  {
                .size =  {
                    0,
                    0,
                    0
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            }
        }
    },
    {
        .flags =  ZYDIS_INSTR_ENC_FLAG_HAS_IMM0,
        .disp =  {
            .size =  {
                0,
                0,
                0
            }
        },
        .imm =  {
            [0] =  {
                .size =  {
                    8,
                    8,
                    8
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            },
            [1] =  {
                .size =  {
                    0,
                    0,
                    0
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            }
        }
    },
    {
        .flags =  ZYDIS_INSTR_ENC_FLAG_HAS_IMM0,
        .disp =  {
            .size =  {
                0,
                0,
                0
            }
        },
        .imm =  {
            [0] =  {
                .size =  {
                    8,
                    8,
                    8
                },
                .is_signed =  ZYAN_TRUE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            },
            [1] =  {
                .size =  {
                    0,
                    0,
                    0
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            }
        }
    },
    {
        .flags =  ZYDIS_INSTR_ENC_FLAG_HAS_IMM0,
        .disp =  {
            .size =  {
                0,
                0,
                0
            }
        },
        .imm =  {
            [0] =  {
                .size =  {
                    8,
                    8,
                    8
                },
                .is_signed =  ZYAN_TRUE,
                .is_address =  ZYAN_TRUE,
                .is_relative =  ZYAN_TRUE
            },
            [1] =  {
                .size =  {
                    0,
                    0,
                    0
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            }
        }
    },
    {
        .flags =  ZYDIS_INSTR_ENC_FLAG_HAS_IMM0,
        .disp =  {
            .size =  {
                0,
                0,
                0
            }
        },
        .imm =  {
            [0] =  {
                .size =  {
                    16,
                    16,
                    16
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            },
            [1] =  {
                .size =  {
                    0,
                    0,
                    0
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            }
        }
    },
    {
        .flags =  ZYDIS_INSTR_ENC_FLAG_HAS_IMM0 | ZYDIS_INSTR_ENC_FLAG_HAS_IMM1,
        .disp =  {
            .size =  {
                0,
                0,
                0
            }
        },
        .imm =  {
            [0] =  {
                .size =  {
                    16,
                    16,
                    16
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            },
            [1] =  {
                .size =  {
                    8,
                    8,
                    8
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            }
        }
    },
    {
        .flags =  ZYDIS_INSTR_ENC_FLAG_HAS_IMM0 | ZYDIS_INSTR_ENC_FLAG_HAS_IMM1,
        .disp =  {
            .size =  {
                0,
                0,
                0
            }
        },
        .imm =  {
            [0] =  {
                .size =  {
                    16,
                    32,
                    32
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_TRUE,
                .is_relative =  ZYAN_FALSE
            },
            [1] =  {
                .size =  {
                    16,
                    16,
                    16
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_TRUE,
                .is_relative =  ZYAN_FALSE
            }
        }
    },
    {
        .flags =  ZYDIS_INSTR_ENC_FLAG_HAS_IMM0,
        .disp =  {
            .size =  {
                0,
                0,
                0
            }
        },
        .imm =  {
            [0] =  {
                .size =  {
                    16,
                    32,
                    32
                },
                .is_signed =  ZYAN_TRUE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            },
            [1] =  {
                .size =  {
                    0,
                    0,
                    0
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            }
        }
    },
    {
        .flags =  ZYDIS_INSTR_ENC_FLAG_HAS_IMM0,
        .disp =  {
            .size =  {
                0,
                0,
                0
            }
        },
        .imm =  {
            [0] =  {
                .size =  {
                    16,
                    32,
                    32
                },
                .is_signed =  ZYAN_TRUE,
                .is_address =  ZYAN_TRUE,
                .is_relative =  ZYAN_TRUE
            },
            [1] =  {
                .size =  {
                    0,
                    0,
                    0
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            }
        }
    },
    {
        .flags =  ZYDIS_INSTR_ENC_FLAG_HAS_IMM0,
        .disp =  {
            .size =  {
                0,
                0,
                0
            }
        },
        .imm =  {
            [0] =  {
                .size =  {
                    16,
                    32,
                    64
                },
                .is_signed =  ZYAN_TRUE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            },
            [1] =  {
                .size =  {
                    0,
                    0,
                    0
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            }
        }
    },
    {
        .flags =  ZYDIS_INSTR_ENC_FLAG_HAS_IMM0,
        .disp =  {
            .size =  {
                0,
                0,
                0
            }
        },
        .imm =  {
            [0] =  {
                .size =  {
                    32,
                    32,
                    32
                },
                .is_signed =  ZYAN_TRUE,
                .is_address =  ZYAN_TRUE,
                .is_relative =  ZYAN_TRUE
            },
            [1] =  {
                .size =  {
                    0,
                    0,
                    0
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            }
        }
    },
    {
        .flags =  ZYDIS_INSTR_ENC_FLAG_HAS_IMM0,
        .disp =  {
            .size =  {
                0,
                0,
                0
            }
        },
        .imm =  {
            [0] =  {
                .size =  {
                    64,
                    64,
                    64
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_TRUE,
                .is_relative =  ZYAN_FALSE
            },
            [1] =  {
                .size =  {
                    0,
                    0,
                    0
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            }
        }
    },
    {
        .flags =  ZYDIS_INSTR_ENC_FLAG_HAS_DISP,
        .disp =  {
            .size =  {
                16,
                32,
                64
            }
        },
        .imm =  {
            [0] =  {
                .size =  {
                    0,
                    0,
                    0
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            },
            [1] =  {
                .size =  {
                    0,
                    0,
                    0
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            }
        }
    },
    {
        .flags =  ZYDIS_INSTR_ENC_FLAG_HAS_MODRM,
        .disp =  {
            .size =  {
                0,
                0,
                0
            }
        },
        .imm =  {
            [0] =  {
                .size =  {
                    0,
                    0,
                    0
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            },
            [1] =  {
                .size =  {
                    0,
                    0,
                    0
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            }
        }
    },
    {
        .flags =  ZYDIS_INSTR_ENC_FLAG_HAS_MODRM | ZYDIS_INSTR_ENC_FLAG_FORCE_REG_FORM,
        .disp =  {
            .size =  {
                0,
                0,
                0
            }
        },
        .imm =  {
            [0] =  {
                .size =  {
                    0,
                    0,
                    0
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            },
            [1] =  {
                .size =  {
                    0,
                    0,
                    0
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            }
        }
    },
    {
        .flags =  ZYDIS_INSTR_ENC_FLAG_HAS_MODRM | ZYDIS_INSTR_ENC_FLAG_HAS_IMM0,
        .disp =  {
            .size =  {
                0,
                0,
                0
            }
        },
        .imm =  {
            [0] =  {
                .size =  {
                    8,
                    8,
                    8
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            },
            [1] =  {
                .size =  {
                    0,
                    0,
                    0
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            }
        }
    },
    {
        .flags =  ZYDIS_INSTR_ENC_FLAG_HAS_MODRM | ZYDIS_INSTR_ENC_FLAG_HAS_IMM0 | ZYDIS_INSTR_ENC_FLAG_HAS_IMM1,
        .disp =  {
            .size =  {
                0,
                0,
                0
            }
        },
        .imm =  {
            [0] =  {
                .size =  {
                    8,
                    8,
                    8
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            },
            [1] =  {
                .size =  {
                    8,
                    8,
                    8
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            }
        }
    },
    {
        .flags =  ZYDIS_INSTR_ENC_FLAG_HAS_MODRM | ZYDIS_INSTR_ENC_FLAG_HAS_IMM0,
        .disp =  {
            .size =  {
                0,
                0,
                0
            }
        },
        .imm =  {
            [0] =  {
                .size =  {
                    8,
                    8,
                    8
                },
                .is_signed =  ZYAN_TRUE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            },
            [1] =  {
                .size =  {
                    0,
                    0,
                    0
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            }
        }
    },
    {
        .flags =  ZYDIS_INSTR_ENC_FLAG_HAS_MODRM | ZYDIS_INSTR_ENC_FLAG_HAS_IMM0,
        .disp =  {
            .size =  {
                0,
                0,
                0
            }
        },
        .imm =  {
            [0] =  {
                .size =  {
                    16,
                    32,
                    32
                },
                .is_signed =  ZYAN_TRUE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            },
            [1] =  {
                .size =  {
                    0,
                    0,
                    0
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            }
        }
    },
    {
        .flags =  ZYDIS_INSTR_ENC_FLAG_HAS_MODRM | ZYDIS_INSTR_ENC_FLAG_HAS_IMM0,
        .disp =  {
            .size =  {
                0,
                0,
                0
            }
        },
        .imm =  {
            [0] =  {
                .size =  {
                    16,
                    32,
                    32
                },
                .is_signed =  ZYAN_TRUE,
                .is_address =  ZYAN_TRUE,
                .is_relative =  ZYAN_TRUE
            },
            [1] =  {
                .size =  {
                    0,
                    0,
                    0
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            }
        }
    },
    {
        .flags =  ZYDIS_INSTR_ENC_FLAG_HAS_MODRM | ZYDIS_INSTR_ENC_FLAG_HAS_IMM0,
        .disp =  {
            .size =  {
                0,
                0,
                0
            }
        },
        .imm =  {
            [0] =  {
                .size =  {
                    32,
                    32,
                    32
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            },
            [1] =  {
                .size =  {
                    0,
                    0,
                    0
                },
                .is_signed =  ZYAN_FALSE,
                .is_address =  ZYAN_FALSE,
                .is_relative =  ZYAN_FALSE
            }
        }
    }
};
